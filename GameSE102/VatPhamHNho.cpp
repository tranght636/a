#include "VatPhamHNho.h"
#define ANI_VAT_PHAM_HNHO 72

VatPhamHNho::VatPhamHNho() : VatPham()
{
	ani = 0;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANI_VAT_PHAM_HNHO));
}

VatPhamHNho::~VatPhamHNho()
{
}

void VatPhamHNho::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	VatPham::Update(dt, colliable_objects);

}

void VatPhamHNho::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void VatPhamHNho::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 15;
}
