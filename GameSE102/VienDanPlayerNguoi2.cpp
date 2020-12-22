#include "VienDanPlayerNguoi2.h"
#include "Brick.h"
#include "QuaiVat.h"
#include "VatPham.h"
#include "Boss.h"





VienDanPlayerNguoi2::VienDanPlayerNguoi2()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(103));
	this->isDirRight = isDirRight;
	ani = 0;
	this->vy = -0.2f;
}


VienDanPlayerNguoi2::~VienDanPlayerNguoi2()
{
}

VienDanPlayerNguoi2::VienDanPlayerNguoi2(int huong) {
	// gán hình cho viên đạn
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(103));
	this->isDirRight = isDirRight;
	this->vx = this->isDirRight ? Vx_VIEN_DAN : -Vx_VIEN_DAN;
	if (huong == 1) {
		this->vx = Vx_VIEN_DAN;
		this->vy = 0;
	}
	else if (huong == 2) {
		this->vx = -Vx_VIEN_DAN;
		this->vy = 0;
	}
	else if (huong == 3) {
		this->vx = 0;
		this->vy = Vx_VIEN_DAN;
	}
	else if (huong == 4) {
		this->vx = 0;
		this->vy = -Vx_VIEN_DAN;
	}
	ani = 0;

}

void VienDanPlayerNguoi2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt);
	this->x += this->dx;
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
		// Lấy từng object để xử lý
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<QuaiVat*>(e->obj)) { // nếu viên đạn gặp quái vật

				if (dynamic_cast<Boss*>(e->obj)) {
					Boss::getInstance()->truMau();
					continue;
				}

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

void VienDanPlayerNguoi2::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y, !isDirRight);	// tấm hình viên đạn bị lật ngược
}

void VienDanPlayerNguoi2::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 8;
	top = y + 2;
	right = x + 14;
	bottom = y + 8;
}
void VienDanPlayerNguoi2::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
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