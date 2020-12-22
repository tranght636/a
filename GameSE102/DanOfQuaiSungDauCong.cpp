#include "DanOfQuaiSungDauCong.h"
#include "Brick.h"
#define ANI_DAN_OF_QUAI_VAT_SUNG_DAU_CONG 102

DanOfQuaiSungDauCong::DanOfQuaiSungDauCong()
{

}
DanOfQuaiSungDauCong::DanOfQuaiSungDauCong(float vx,float vy)
{
	// set ani_set_id ở đây 
	ani = 0;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANI_DAN_OF_QUAI_VAT_SUNG_DAU_CONG));

	this->vx = vx;
	this->vy = vy;
}

DanOfQuaiSungDauCong::~DanOfQuaiSungDauCong()
{
}

void DanOfQuaiSungDauCong::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt);
	// Lọc brick,
	vector<LPGAMEOBJECT> objectFilter;
	filterCoObject(&objectFilter, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(&objectFilter, coEvents);
	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
		return;
	}
	if (coEvents.size() != 0) {
		float min_tx, min_ty, nx = 0, ny;
		vector<LPCOLLISIONEVENT> coEventsResult;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// Lấy từng object để xử lý
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Brick*>(e->obj)) {
				this->ani = 1;
				this->release();
			}
		}


	}
}

void DanOfQuaiSungDauCong::Render() {
	animation_set->at(ani)->Render(x, y);
}

void DanOfQuaiSungDauCong::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 7;
	bottom = y + 7;
}
void DanOfQuaiSungDauCong::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
	// Lấy từng object để xử lý
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Brick*>(coObjects->at(i))) // Nếu va chạm với đất
		{
			kq->push_back(coObjects->at(i));
		}
	}
}