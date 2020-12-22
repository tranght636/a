#include "QuaiVatRuoi.h"
#include "Brick.h"
#include "Utils.h"

#define VY_RUOI	0.02f
#define S_LEN 25
#define S_XUONG	20

#define STATUS_BINH_THUONG	1
#define STATUS_ROT 2

QuaiVatRuoi::QuaiVatRuoi() : QuaiVat()
{
	this->vx = 0.02f;
	this->vy = VY_RUOI;
	this->status = STATUS_BINH_THUONG;
	this->isDirRight = true;
	this->ani = 0;
}


QuaiVatRuoi::~QuaiVatRuoi()
{
}
int temp = 1;
void QuaiVatRuoi::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// lọc gạch
	vector<LPGAMEOBJECT> objectFilter;
	filterCoObject(&objectFilter, coObjects);

	this->vx = this->isDirRight ? 0.02f : -0.02f;
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(&objectFilter, coEvents);

	if (coEvents.size() == 0) {
		switch (this->status)
		{
		case STATUS_BINH_THUONG: {
			if (y - start_y > S_XUONG) {
				vy = -VY_RUOI * 7;
				start_y = y;
			}
			else if (start_y - y > S_LEN) {
				vy = VY_RUOI;
				start_y = y;
			}

			break;
		}
		case STATUS_ROT: {
			vy = 10 * VY_RUOI;
			break;
		}
			
		default:
			break;
		}

		// cập nhật vị trí
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		vector<LPCOLLISIONEVENT> coEventsResult;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.5f;
		y += min_ty * dy + ny * 0.5f;
		if (nx != 0) vx = 0;	// không cho đi khi xảy ra va chạm
		if (ny != 0) vy = 0;

		// Lấy từng object để xử lý
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Brick*>(e->obj)) // Nếu va chạm với đất
			{
				Brick* brick = dynamic_cast<Brick*>(e->obj);
				if (e->nx != 0) {
					this->isDirRight = !isDirRight;
					//this->vx *= -1;
				}
				if (e->ny < 0 && this->status == STATUS_ROT) {
					this->status = STATUS_BINH_THUONG;
					start_y = y;
					vy = -7 * VY_RUOI;
				} 
				if (e->ny > 0 && this->status == STATUS_BINH_THUONG) {
					this->status = STATUS_ROT;
				}
				if (e->ny < 0 && this->status == STATUS_BINH_THUONG) {
					start_y = y;
					vy = -7 * VY_RUOI;
				}
			}
		}
	}
	
}


void QuaiVatRuoi::Render() {
	animation_set->at(ani)->Render(x, y, vx > 0);
}

void QuaiVatRuoi::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 1;
	top = y + 1;
	right = x + 17;
	bottom = y + 15;
}
void QuaiVatRuoi::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
	// Lấy từng object để xử lý
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Brick*>(coObjects->at(i))) // Nếu va chạm với đất
		{
			kq->push_back(coObjects->at(i));
		}
	}
}