#pragma once
#include "GameObject.h"

class Stair: public CGameObject
{
	int isTop;
	int isRightStair;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL) override;
	Stair(float x, float y, float width, float height, int isTop, int isRightStair);
	Stair();
	~Stair();
};