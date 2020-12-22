#include "DenCay.h"
#include "CPlayer.h"
#define	DEN_CAY_VX 0.04

DenCay::DenCay()
{
	vx = DEN_CAY_VX;
}


DenCay::~DenCay()
{
}


void DenCay::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CPlayer* player = CPlayer::getInstane();
	if (Collision::checkAABB(this, player->getWeapon())) {
		this->setY(-50);
	}

	/*CGameObject::Update(dt);
	x -= dx;*/
}

void DenCay::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void DenCay::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 8;
	bottom = y + 16;
}