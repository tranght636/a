#include "VienDan1Trai.h"
#include "Brick.h"
#include "QuaiVat.h"
#include "Camera.h"
#include "VatPham.h"




VienDan1Trai::VienDan1Trai()
{
	
}


VienDan1Trai::~VienDan1Trai()
{
}

VienDan1Trai::VienDan1Trai(int isDirRight) {
	// gán hình cho viên đạn
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANI_VIEN_DAN_1_TRAI));
	this->isDirRight = isDirRight;
	this->vx = this->isDirRight? Vx_VIEN_DAN : -Vx_VIEN_DAN;
}
VienDan1Trai::VienDan1Trai(int isDirRight, float vx, float vy) {
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANI_VIEN_DAN_1_TRAI));
	this->isDirRight = isDirRight;
	this->vx = this->isDirRight ? Vx_VIEN_DAN : -Vx_VIEN_DAN;
	this->vy = vy;
	this->ani = this->isDirRight?0:1;
}

void VienDan1Trai::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt);
	this->x += this->dx;

	float leftCam = Camera::getInstance()->getLeft();
	float rightCam = Camera::getInstance()->getRight();
	
	if (this->x > rightCam - 15 || this->x < leftCam) {
		this->release();
		return;
	}

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
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void VienDan1Trai::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y, !isDirRight);	// tấm hình viên đạn bị lật ngược
}

void VienDan1Trai::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 8;
	top = y + 2;
	right = x + 14;
	bottom = y + 8;
}
void VienDan1Trai::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
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