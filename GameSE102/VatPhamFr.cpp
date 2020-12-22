#include "VatPhamFr.h"
#define ANI_VAT_PHAM_Fr 71

VatPhamFr::VatPhamFr() : VatPham()
{
	ani = 0;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANI_VAT_PHAM_Fr));
}


VatPhamFr::~VatPhamFr()
{
}

void VatPhamFr::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	VatPham::Update(dt, colliable_objects);

}

void VatPhamFr::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void VatPhamFr::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 15;
}
