#include "QuaiVatDauSau.h"
#include "Brick.h"
#include "Utils.h"
#include "DanOfQuaiVatDauSau.h"
#include "PlayScence.h"


QuaiVatDauSau::QuaiVatDauSau() : QuaiVat()
{
	vx = vy = 0.05f;
}


QuaiVatDauSau::~QuaiVatDauSau()
{
}

void QuaiVatDauSau::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// Lọc brick,
	vector<LPGAMEOBJECT> objectFilter;
	filterCoObject(&objectFilter, coObjects);

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(&objectFilter, coEvents);
	
	// Xử lý bình thường
	if (coEvents.size() == 0) {
		
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		vector<LPCOLLISIONEVENT> coEventsResult;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// Lấy từng object để xử lý
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Brick*>(e->obj)) // Nếu va chạm với đất
			{
				Brick* brick = dynamic_cast<Brick*>(e->obj);
				if (e->ny < 0 || e->ny > 0)	//ny < 0 đáy player chạm trên của đất
				{	
					vy *= -1;
					CGameObject::Update(dt);
					y += dy;
				}
				else {
					vx *= -1;
					CGameObject::Update(dt);
					x += dx;
				}
			}
		}


	}
	
	if (this->timeDelay->delay(2000)) {
		Camera* cam = Camera::getInstance();
		if (this->x < cam->getX() || this->x > cam->getX() + cam->getWidth() ||
			 this->y < cam->getY() || this->y > cam->getY() + cam->getHeight())
		{
			return;
		}
		DanOfQuaiVatDauSau* vienDan = new DanOfQuaiVatDauSau();
		vienDan->setX(this->x);
		vienDan->setY(this->y);
		vienDan->setV();
		CPlayScene::addObjectToGrid(vienDan);
	}
	
}

void QuaiVatDauSau::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void QuaiVatDauSau::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 19;
	bottom = y + 16;
}
void QuaiVatDauSau::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
	// Lấy từng object để xử lý
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Brick*>(coObjects->at(i))) // Nếu va chạm với đất
		{
			kq->push_back(coObjects->at(i));
		}
	}
}