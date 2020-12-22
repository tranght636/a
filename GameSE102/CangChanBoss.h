#pragma once
#include "QuaiVat.h"

class CangChanBoss : public QuaiVat
{
	float xTuongDoi, yTuongDoi;

public:
	CangChanBoss();
	CangChanBoss(float x, float y);
	~CangChanBoss();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;

	float getXTuongDoi() { return this->xTuongDoi; }
	float getYTuongDoi() { return this->yTuongDoi; }

	void setXTuongDoi(float xTuongDoi) { this->xTuongDoi = xTuongDoi; }
};
