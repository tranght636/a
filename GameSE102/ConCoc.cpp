#include "ConCoc.h"
#include "CPlayer.h"

#define	LINH_VX 0.04
ConCoc::ConCoc()
{
	vx = LINH_VX;

}

ConCoc::~ConCoc()
{
}

void ConCoc::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CPlayer* player = CPlayer::getInstane();
	if (Collision::checkAABB(this, player->getWeapon())) {
		this->release();
		return;
	}

	/*CGameObject::Update(dt);
	x += dx;*/
}

void ConCoc::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void ConCoc::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 32;
}