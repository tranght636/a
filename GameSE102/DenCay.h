#pragma once
#include "GameObject.h"

class DenCay : public CGameObject
{
public:
	DenCay();
	~DenCay();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
};