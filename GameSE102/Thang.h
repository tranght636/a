#pragma once
#include "GameObject.h"

class Thang : public CGameObject
{
	bool isThangLen;
public:
	Thang(float l, float t, float w, float h, bool isThangLen);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;

};

