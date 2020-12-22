#include "QuaiVatDauLau.h"
#include "PlayerXe.h"
#include "Brick.h"
#include "CPlayer.h"
#include "PlayerNguoi.h"

#include "DanOfQuaiVatDauLau.h"
#include "PlayScence.h"

#define TOC_DO_DAU_LAU 0.15f

#define STATUS_DOI_DI_CHUYEN 0
#define STATUS_DI_CHUYEN_LAN_1 1
#define STATUS_DI_CHUYEN_LAN_2 2
#define STATUS_DI_CHUYEN_NGUOC 3
#define STATUS_DOI_DI_CHUYEN_LAN_2 4
#define STATUS_BAN_LAN_2 5


QuaiVatDauLau::QuaiVatDauLau() : QuaiVat()
{
	vy = 0;
	this->width = 18;
	this->height = 18;
	this->status = STATUS_DOI_DI_CHUYEN;
}


QuaiVatDauLau::~QuaiVatDauLau()
{
}

void QuaiVatDauLau::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	int dtx = this->getMidX() - CPlayer::getPlayerHienTai()->getMidX();
	int dty = this->getMidY() - CPlayer::getPlayerHienTai()->getMidY();

	switch (this->status)
	{
	case STATUS_DOI_DI_CHUYEN: 
		if (abs(dtx) < 216 && abs(dty) < 120) {
			this->vx = dtx > 0 ? -TOC_DO_DAU_LAU : TOC_DO_DAU_LAU;
			this->vLan2 = this->vx;
			this->status = STATUS_DI_CHUYEN_LAN_1;
		}
		break;
	
	case STATUS_DI_CHUYEN_LAN_1:
		CGameObject::Update(dt);
		x += dx;
		this->isDirRight = vx > 0;
		
		// check sinh dan
		if (abs(dtx) < 5) {
			DanOfQuaiVatDauLau* vienDan = new DanOfQuaiVatDauLau();
			vienDan->setX(this->x);
			vienDan->setY(this->y);
			vienDan->setStart(this->x, this->y);
			CPlayScene::addObjectToGrid(vienDan);

			this->vy = -0.1f;
			this->status = STATUS_DI_CHUYEN_NGUOC;
			this->start_x = x;
			this->isDirRight = !this->isDirRight;
		}
		break;

	case STATUS_DI_CHUYEN_NGUOC: {
		CGameObject::Update(dt);
		vx = 0;
		y += dy;

		vector<LPGAMEOBJECT> objectFilter;
		filterCoObject(&objectFilter, coObjects);

		vector<LPCOLLISIONEVENT> coEvents;
		coEvents.clear();
		CalcPotentialCollisions(&objectFilter, coEvents);

		if (coEvents.size() != 0) {
			float min_tx, min_ty, nx = 0, ny;
			vector<LPCOLLISIONEVENT> coEventsResult;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// Lấy từng object để xử lý
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<Brick*>(e->obj)) // Nếu va chạm với đất
				{
					if (e->ny > 0)	//ny < 0 đáy player chạm trên của đất
					{
						vy = 0;
						this->status = STATUS_DOI_DI_CHUYEN_LAN_2;
					}
				}
			}
		}
		break;
	}

	case STATUS_DOI_DI_CHUYEN_LAN_2:
		if (abs(dtx) > 40) {
			this->status = STATUS_BAN_LAN_2;
		}
		break;
		
	case STATUS_BAN_LAN_2:
		if (abs(dtx) < 5) {
			// check sinh dan
			if (abs(dtx) < 1) {
				DanOfQuaiVatDauLau* vienDan = new DanOfQuaiVatDauLau();
				vienDan->setX(this->x);
				vienDan->setY(this->y);
				vienDan->setStart(this->x, this->y);
				CPlayScene::addObjectToGrid(vienDan);

				this->vy = -0.1f;
				this->vx = this->vLan2;
				this->status = STATUS_DI_CHUYEN_LAN_2;
				
			}
		}
		break;

	case STATUS_DI_CHUYEN_LAN_2: {
		CGameObject::Update(dt);
		this->isDirRight = vx > 0;
		x += dx;

		if (abs(this->x - this->start_x) > 70) {
			this->release();
		}
		break;
	}

	default:
		break;
	}

	
}

void QuaiVatDauLau::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y, this->isDirRight);
}

void QuaiVatDauLau::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 19;
	bottom = y + 16;
}

void QuaiVatDauLau::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
	// Lấy từng object để xử lý
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Brick*>(coObjects->at(i))) // Nếu va chạm với đất
		{
			kq->push_back(coObjects->at(i));
		}
	}
}