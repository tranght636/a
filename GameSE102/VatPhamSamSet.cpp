#include "VatPhamSamSet.h"
#define ANI_VAT_PHAM_SAM_SET 73

VatPhamSamSet::VatPhamSamSet() : VatPham()
{
	ani = 0;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANI_VAT_PHAM_SAM_SET));
}

VatPhamSamSet::~VatPhamSamSet()
{
}

void VatPhamSamSet::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	VatPham::Update(dt, colliable_objects);
}

void VatPhamSamSet::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void VatPhamSamSet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 15;
}
