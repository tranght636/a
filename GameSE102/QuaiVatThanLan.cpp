#include "QuaiVatThanLan.h"
#include "Brick.h"
#include "PlayerXe.h"

QuaiVatThanLan::QuaiVatThanLan() : QuaiVat()
{
	vx = 0.07f;
	vy = 0.1f;
}


QuaiVatThanLan::~QuaiVatThanLan()
{
}

void QuaiVatThanLan::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	int dtx = this->getMidX() -PlayerXe::getInstance()->getMidX();
	int dty = this->getMidY() - PlayerXe::getInstance()->getMidY();

	if (abs(dtx) >= 60 || abs(dty)>=40) {
		this->isTanCong = false;
	}

	if (this->isTanCong || (abs(dtx) < 60 && abs(dty) < 40)) {
		if (this->isChamDat) {
			this->vy = -0.2f;
			this->isChamDat = false;
		}
		
		this->isTanCong = true;
		
	}
	

	// Lọc brick,
	vector<LPGAMEOBJECT> objectFilter;
	filterCoObject(&objectFilter, coObjects);

	CGameObject::Update(dt);
	vy += 0.001 * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(&objectFilter, coEvents);

	// Xử lý bình thường
	if (coEvents.size() == 0) {
		y += dy;
		this->x += dx;
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
					this->isChamDat = true;
					if (this->isTanCong) {
						this->vx = dtx > 0 ? -0.07f : 0.07f;
					}
					
				}
				if (e->nx != 0) {
					vx *= -1;
				}

				//this->x += dx;
			}
		}


	}

	
}

void QuaiVatThanLan::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y, vx > 0);
}

void QuaiVatThanLan::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 26;
}
void QuaiVatThanLan::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
	// Lấy từng object để xử lý
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Brick*>(coObjects->at(i))) // Nếu va chạm với đất
		{
			kq->push_back(coObjects->at(i));
		}
	}
}