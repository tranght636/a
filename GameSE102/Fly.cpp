#include "Fly.h"
#include "CPlayer.h"

#define	LINH_VX 0.04
Fly::Fly()
{
	vx = LINH_VX;
}

Fly::~Fly()
{
}

void Fly::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CPlayer* player = CPlayer::getInstane();
	if (Collision::checkAABB(this, player->getWeapon())) {
		this->setY(-50);
	}

	/*CGameObject::Update(dt);
	x += dx;*/
}

void Fly::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void Fly::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 32;
}