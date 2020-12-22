#include "BanChanBoss.h"
#include "Boss.h"

#define ANI_QUAI_VAT_BAN_CHAN_BOSS	602

BanChanBoss::BanChanBoss()
{

}
BanChanBoss::BanChanBoss(float x, float y) {
	this->xTuongDoi = x;
	this->yTuongDoi = y;

	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANI_QUAI_VAT_BAN_CHAN_BOSS));
	this->ani = 0;
}

BanChanBoss::~BanChanBoss()
{
}

void BanChanBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CGameObject::Update(dt);

	this->xTuongDoi += dx;
	this->yTuongDoi += dy;

	this->x = Boss::getInstance()->getX() + this->xTuongDoi;
	this->y = Boss::getInstance()->getY() + this->yTuongDoi;
}

void BanChanBoss::Render() {
	animation_set->at(ani)->Render(x, y);
}

void BanChanBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 19;
	bottom = y + 16;
}
