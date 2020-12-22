#pragma once
#include "QuaiVat.h"

class Duoc : public QuaiVat
{
public:
	Duoc();
	~Duoc();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void createItem(float x, float y);
};

