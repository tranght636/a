#include "VatPhamP.h"
#define ANI_VAT_PHAM_P 70

VatPhamP::VatPhamP() : VatPham()
{
	ani = 0;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANI_VAT_PHAM_P));
}

VatPhamP::~VatPhamP()
{
}

void VatPhamP::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	VatPham::Update(dt, colliable_objects);

}

void VatPhamP::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void VatPhamP::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 15;
}
