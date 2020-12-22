#include "VienDan1Len.h"
#include "QuaiVat.h"
#include "VatPham.h"



VienDan1Len::VienDan1Len()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(4));
	this->isDirRight = isDirRight;
	this->vy = -0.2f;
}
VienDan1Len::VienDan1Len(float vx,float vy) {
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(4));
	this->vx = vx;
	this->vy = vy;
	this->isDirRight = isDirRight;
	this->ani = this->vy > 0? 0 : 1;
}

VienDan1Len::~VienDan1Len()
{
}

void VienDan1Len::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt);
	this->y += this->dy;

	vector<LPGAMEOBJECT> objectFilter;
	filterCoObject(&objectFilter, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(&objectFilter, coEvents);
	if (coEvents.size() != 0)	// tức là có va chạm
	{
		float min_tx, min_ty, nx = 0, ny;
		vector<LPCOLLISIONEVENT> coEventsResult;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;
		// Lấy từng object để xử lý
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<QuaiVat*>(e->obj)) { // nếu viên đạn gặp quái vật
				QuaiVat* quaiVat = dynamic_cast<QuaiVat*>(e->obj);
				quaiVat->NewItem();
				quaiVat->release();	// xoá quái vật
			}
		}
		
		this->release(); // tự xoá chính nó
		return;
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void VienDan1Len::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void VienDan1Len::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 7;
	bottom = y + 25;
}
void VienDan1Len::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
	// Lấy từng object để xử lý
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<VatPham*>(coObjects->at(i))) // Nếu va chạm với đất
		{
			continue;
		}
		kq->push_back(coObjects->at(i));
	}
}