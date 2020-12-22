#include "DanOfQuaiVatDauLau.h"
#include "PlayerXe.h"
#include "Brick.h"
#include "CPlayer.h"
#include "PlayerNguoi.h"


DanOfQuaiVatDauLau::DanOfQuaiVatDauLau()
{
	vx = 0;
	vy = 0.2f;
	this->ani = 0;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANI_DAN_OF_QUAI_VAT_DAU_LAU));


}

DanOfQuaiVatDauLau::~DanOfQuaiVatDauLau()
{
}

void DanOfQuaiVatDauLau::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (abs(this->start_x - this->x) >= 120) {
		this->release();
	}
	
	// Lọc brick,
	vector<LPGAMEOBJECT> objectFilter;
	filterCoObject(&objectFilter, coObjects);

	CGameObject::Update(dt);
	//this->vy = 0.1f;

	// Lấy danh sách va chạm với Player
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(&objectFilter, coEvents);

	if (coEvents.size() == 0) {
		if (this->nay) {
			this->vy += 0.002 * dt;
		}
		y += dy;
		x += dx;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		vector<LPCOLLISIONEVENT> coEventsResult;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// Lấy từng object để xử lý
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Brick*>(e->obj)) {

				if (e->nx != 0) {
					this->release();
				}

				y += min_ty * dy + ny * 0.5f;
				vy = 0;
				// nẩy cái khi chạm đất r lăn về hướng layer
				if (!this->nay) {
					vy = -0.2f;
					this->nay = true;
					vx = x - CPlayer::getPlayerHienTai()->getX() > 0 ? -0.1f : 0.1f;
				}
			}
		}
	}
}

void DanOfQuaiVatDauLau::Render() {

	animation_set->at(ani)->Render(x, y);
}

void DanOfQuaiVatDauLau::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y ;
	right = x + 8;
	bottom = y + 8;
}
void DanOfQuaiVatDauLau::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
	// Lấy từng object để xử lý
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Brick*>(coObjects->at(i))) // Nếu va chạm với đất
		{
			kq->push_back(coObjects->at(i));
		}
	}
}