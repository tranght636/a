#include "VatPham.h"

VatPham::VatPham()
{
	
}


VatPham::~VatPham()
{
}

void VatPham::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	if (isTime == true) {
		if (this->timeDelay->delay(2000)) {
			this->release();
		}
	}
}

void VatPham::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void VatPham::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 25;
	bottom = y + 25;
}
