#include "QuaiVatSau.h"
#include "Brick.h"
#include "CPlayer.h"


QuaiVatSau::QuaiVatSau() : QuaiVat()
{
	
	this->vx = -0.08f;
}


QuaiVatSau::~QuaiVatSau()
{
}

void QuaiVatSau::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// khi con player toi gan thi moi chay ham update nay
	if (0) {
		return;
	}
	
	if (this->x <= this->gioiHanTrai || this->x >= this->gioiHanPhai) {
		this->vx *= -1;
		this->x += vx > 0 ? 5 : -5;
	}

	CGameObject::Update(dt);
	this->vy = 0.15f;
	

	// Lọc brick,
	vector<LPGAMEOBJECT> objectFilter;
	filterCoObject(&objectFilter, coObjects);

	// Lấy danh sách va chạm với Player
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(&objectFilter, coEvents);

	// Xử lý bình thường
	if (coEvents.size() == 0) {
		// Con sâu luôn rớt xuống
		this->y += dy;

		
		return;
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
				if (e->ny < 0)	//ny < 0 đáy player chạm trên của đất
				{
					vy = 0;
					y += min_ty * dy + ny * 0.1f;
				}
				this->x += dx;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void QuaiVatSau::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
	// Lấy từng object để xử lý
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Brick*>(coObjects->at(i))) // Nếu va chạm với đất
		{
			kq->push_back(coObjects->at(i));
		}
	}
}

void QuaiVatSau::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y, this->vx > 0);
}

void QuaiVatSau::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 1;
	top = y + 1;
	right = x + 17;
	bottom = y + 7;
}
