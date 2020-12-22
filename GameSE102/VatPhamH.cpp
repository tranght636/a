#include "VatPhamH.h"
#define ANI_VAT_PHAM_H 74

VatPhamH::VatPhamH() : VatPham()
{
	ani = 0;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANI_VAT_PHAM_H));
}

VatPhamH::~VatPhamH()
{
}

void VatPhamH::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	VatPham::Update(dt, colliable_objects);

}

void VatPhamH::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void VatPhamH::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 15;
}
