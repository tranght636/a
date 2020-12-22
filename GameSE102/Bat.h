#pragma once
#include "QuaiVat.h"

class Bat : public QuaiVat
{
public:
	Bat();
	~Bat();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
};