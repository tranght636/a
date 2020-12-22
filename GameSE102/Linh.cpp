#include "Linh.h"
#include "CPlayer.h"

#define	LINH_VX 0.04

int xQuayDauTrai;

Linh::Linh()
{
	vx = -LINH_VX;
	vy = 0;
	isNgan = 0;
}

Linh::~Linh()
{
}

void Linh::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CPlayer* player = CPlayer::getInstane();
	if (Collision::checkAABB(this, player->getWeapon())) {
		this->release();
		return;
	}

	CGameObject::Update(dt);
	vy += PLAYER_GRAVITY * dt;

	if (isNgan == 1) {
		xQuayDauTrai = xLon;
	}
	else if(isNgan == 2) {
		xQuayDauTrai = xNho;
	}

	if (x <= xQuayDau) {
		vx = -vx;
		x += 2;
		direction = -1;
		isNgan = isNgan <= 1 ? 2 : 1;
	}
	else if (x >= xQuayDauTrai && isNgan != 0) {
		vx = -vx;
		x -= 2;
		direction = 1;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	vector<LPGAMEOBJECT> coObjects;
	for (unsigned i = 0; i < colliable_objects->size(); i++) {
		LPGAMEOBJECT object = colliable_objects->at(i);
		if (dynamic_cast<Brick*>(object)) {
			coObjects.push_back(object);
		}
	}

	CalcPotentialCollisions(&coObjects, coEvents);
	if (coEvents.size() == 0) {
		y += dy;
		x += dx;
	}
	else {
		float min_tx, min_ty, nx = 0, ny = 0;
		vector<LPCOLLISIONEVENT> coEventsResult;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		y += min_ty * dy + ny * 0.4f;
		x += min_tx * dx + nx * 0.4f;
		if (ny != 0) {
			vy = 0;
		}
	}

	coObjects.clear();
}

void Linh::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y, direction);
}

void Linh::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 32;
}