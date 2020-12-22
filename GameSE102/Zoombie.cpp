#include "Zoombie.h"
#include "CPlayer.h"

Zoombie::Zoombie()
{
	isMove = false;
}


Zoombie::~Zoombie()
{
}


void Zoombie::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects) {
	CPlayer* player = CPlayer::getInstane();
	if (Collision::checkAABB(this, player->getWeapon())) {
		this->setY(-50);
		isMove = false;
	}
	float dxToPlayer2 = player->getX() - this->getStartX();
	float dxToPlayer = abs(dxToPlayer2);
	if (DX_TO_MOVE - 10 < dxToPlayer && dxToPlayer < DX_TO_MOVE && !isMove) {
		getStart(this->x, this->y);
		isMove = true;
		if (dxToPlayer2 > 0) {
			vx = ZOOMBIE_VX;
			direction = -1;
		}
		else if (dxToPlayer2 < 0) {
			vx = -ZOOMBIE_VX;
			direction = 1;
		}
	}

	if (isMove) {
		// Calculate dx, dy 
		CGameObject::Update(dt);
		x += dx;

		if (x < 0 || x > TileMap::getInstance()->getMapWidth()) {
			isMove = false;
		}
	}
	else {
		x = y = -50;
	}
}

void Zoombie::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y,direction);
}

void Zoombie::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 32;
}