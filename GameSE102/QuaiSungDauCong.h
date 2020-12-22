#pragma once
#include "QuaiVat.h"

class QuaiSungDauCong : public QuaiVat
{
public:
	QuaiSungDauCong();
	~QuaiSungDauCong();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
};





