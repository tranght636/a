#include "ChanBoss.h"


ChanBoss::ChanBoss()
{

}


ChanBoss::~ChanBoss()
{
}

void ChanBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CGameObject::Update(dt);
	this->x += dx;
	this->y += dy;
}

void ChanBoss::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void ChanBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 19;
	bottom = y + 16;
}
