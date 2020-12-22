#pragma once
#include "GameObject.h"

class Weapon : public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL) override;
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b) override;
	Weapon();
	~Weapon();
};

