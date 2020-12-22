#include "VienDanPlayerNguoi.h"
#include "Brick.h"
#include "QuaiVat.h"
#include "VatPham.h"






VienDanPlayerNguoi::VienDanPlayerNguoi()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(104));
	this->isDirRight = isDirRight;
	ani = 0;
	this->vy = -0.2f;
}


VienDanPlayerNguoi::~VienDanPlayerNguoi()
{
}

VienDanPlayerNguoi::VienDanPlayerNguoi(int huong) {
	// gán hình cho viên đạn
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(104));
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
	ani = 0;

}

void VienDanPlayerNguoi::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
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

void VienDanPlayerNguoi::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y, !isDirRight);	// tấm hình viên đạn bị lật ngược
}

void VienDanPlayerNguoi::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 1;
	top = y + 1;
	right = x + 3;
	bottom = y + 3;
}
void VienDanPlayerNguoi::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
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