#pragma once
#include "QuaiVat.h"

#define ZOOMBIE_VX 0.04f
#define DX_TO_MOVE	170

class Zoombie : public QuaiVat
{
	bool isMove;
public:
	Zoombie();
	~Zoombie();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;

};

