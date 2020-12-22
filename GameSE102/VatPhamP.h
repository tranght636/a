#pragma once
#include "VatPham.h"

class VatPhamP : public VatPham
{
public:
	VatPhamP();
	~VatPhamP();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
};





