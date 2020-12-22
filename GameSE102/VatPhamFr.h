#pragma once
#include "VatPham.h"

class VatPhamFr : public VatPham
{
public:
	VatPhamFr();
	~VatPhamFr();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
};





