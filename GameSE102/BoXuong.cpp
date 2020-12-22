#include "BoXuong.h"
#include "CPlayer.h"

#define	LINH_VX 0.04
BoXuong::BoXuong()
{
	vx = LINH_VX;

}

BoXuong::~BoXuong()
{
}

void BoXuong::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CPlayer* player = CPlayer::getInstane();
	if (Collision::checkAABB(this, player->getWeapon())) {
		this->release();
		return;
	}

	/*CGameObject::Update(dt);
	x += dx;*/
}

void BoXuong::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void BoXuong::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 32;
}