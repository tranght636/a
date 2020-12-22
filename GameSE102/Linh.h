#pragma once
#include "QuaiVat.h"
class Linh : public QuaiVat
{
	int isNgan;
	float xQuayDau;
	float xLon;
	float xNho;
public:
	Linh();
	~Linh();
	void setXQuay(float x1, float x2, float x3) { this->xQuayDau = x1, this->xNho = x2, this->xLon = x3; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
};