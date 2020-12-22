#include "QuaiVatBoRuaNgang.h"
#include "Brick.h"
#define VX_BO_RUA_NGANG	0.08
QuaiVatBoRuaNgang::QuaiVatBoRuaNgang()
{
	vx = VX_BO_RUA_NGANG;
}


QuaiVatBoRuaNgang::~QuaiVatBoRuaNgang()
{
}

void QuaiVatBoRuaNgang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// Lọc brick,
	vector<LPGAMEOBJECT> objectFilter;
	filterCoObject(&objectFilter, coObjects);

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(&objectFilter, coEvents);

	// Xử lý bình thường
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
				vx *= -1;
			}
		}
	}
	x += dx;
}

void QuaiVatBoRuaNgang::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y,vx>0);
}

void QuaiVatBoRuaNgang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 19;
	bottom = y + 16;
}
void QuaiVatBoRuaNgang::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
	// Lấy từng object để xử lý
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Brick*>(coObjects->at(i))) // Nếu va chạm với đất
		{
			kq->push_back(coObjects->at(i));
		}
	}
}
