#pragma once
#include "QuaiVat.h"

class Fly : public QuaiVat
{
public:
	Fly();
	~Fly();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
};