#include "CangChanBoss.h"
#include "Boss.h"

#define ANI_QUAI_VAT_CANG_CHAN_BOSS	601

CangChanBoss::CangChanBoss()
{

}
CangChanBoss::CangChanBoss(float x, float y) {
	this->vx = 0;
	this->vy = 0;

	this->xTuongDoi = x;
	this->yTuongDoi = y;

	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANI_QUAI_VAT_CANG_CHAN_BOSS));
	ani = 0;
}

CangChanBoss::~CangChanBoss()
{
}

void CangChanBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CGameObject::Update(dt);

	this->xTuongDoi += dx;
	this->yTuongDoi += dy;

	this->x = Boss::getInstance()->getX() + this->xTuongDoi;
	this->y = Boss::getInstance()->getY() + this->yTuongDoi;
}

void CangChanBoss::Render() {
	animation_set->at(ani)->Render(x, y);
}

void CangChanBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 19;
	bottom = y + 16;
}
