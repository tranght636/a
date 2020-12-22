#include "QuaiVatBomz.h"


QuaiVatBomz::QuaiVatBomz() : QuaiVat()
{

}


QuaiVatBomz::~QuaiVatBomz()
{
}

void QuaiVatBomz::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
}

void QuaiVatBomz::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void QuaiVatBomz::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 19;
	bottom = y + 16;
}
