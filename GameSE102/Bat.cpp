#include "bat.h"
#include "CPlayer.h"
#include "TileMap.h"
#define	BAT_VX 0.08
#define BAT_VY 0.04
#define STATE_NGHI	0
#define STATE_CHEO	1
#define STATE_NGANG	2

#define KHOANG_CACH_DE_BAY_X 88
#define KHOANG_CACH_DE_BAY_Y 30

#define ANI_NGU	0
#define ANI_BAY	1



Bat::Bat()
{
	vx = BAT_VX;
	state = STATE_NGHI;
	ani = ANI_NGU;
}


Bat::~Bat()
{
}


void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CPlayer* player = CPlayer::getInstane();
	if (Collision::checkAABB(this, player->getWeapon())) {
		this->release();
		return;
	}
	if (vx > 0 && x > TileMap::getInstance()->getMapWidth()
		|| vx < 0 && x < -20) {
		this->release();
		return;
	}
	float khoangCach = player->getX() - this->x;
	if (state == STATE_NGHI && khoangCach < 0) {
		vx = -BAT_VX;
		direction = 1;
	}
	else {
		vx = BAT_VX;
		direction = -1;
	}

	if (state == STATE_NGHI){
		float absKhoangCach = abs(khoangCach);
		float absKhoangCachY = abs(this->y - player->getY());
		if (absKhoangCach <= KHOANG_CACH_DE_BAY_X && absKhoangCachY <= KHOANG_CACH_DE_BAY_Y) {
			state = STATE_CHEO;
			ani = ANI_BAY;
		}
	}
	else if (state == STATE_CHEO) {
		if (this->y > player->getY() + 8) {
			state = STATE_NGANG;
		}
		else {
			vy = BAT_VY;
			CGameObject::Update(dt);
			this->x += this->dx;
			this->y += this->dy;
		}
	}
	else if (state == STATE_NGANG) {
		vy = 0;
		CGameObject::Update(dt);
		this->x += this->dx;
		this->y += this->dy;
	}

}

void Bat::Render() {
	animation_set->at(ani)->Render(x, y, direction);
}

void Bat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 14;
}