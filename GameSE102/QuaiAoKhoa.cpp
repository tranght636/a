#include "QuaiAoKhoa.h"
#include "PlayScence.h"

QuaiAoKhoa::QuaiAoKhoa()
{
	this->xBD = x;
	this->yBD = y;
}


QuaiAoKhoa::~QuaiAoKhoa()
{
}
bool t = true;
void QuaiAoKhoa::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {

	if (this->timeDelay->delay(t?1000:1200)) {
		t = !t;
		switch (this->diChuyen)
		{
		case 0:
			x = x1; y = y1;
			this->diChuyen = 1;
			break;
		case 1:
			x = x2; y = y2;
			this->diChuyen = 2;
			break;
		case 2:
			x = x3; y = y3;
			this->diChuyen = 3;
			break;
		case 3:
			x = x4; y = y4;
			this->diChuyen = 4;
			break;
		case 4:
			x = x5; y = y5;
			this->diChuyen = 0;
			break;
		default:
			break;
		}
	}

}

void QuaiAoKhoa::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void QuaiAoKhoa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x+2;
	top = y;
	right = x + 25;
	bottom = y + 32;
}
