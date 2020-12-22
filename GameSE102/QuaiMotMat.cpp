#include "QuaiMotMat.h"
#include "CPlayer.h"
#define TOC_DO_MOT_MAT 0.08
QuaiMotMat::QuaiMotMat() : QuaiVat()
{

}


QuaiMotMat::~QuaiMotMat()
{
}

void QuaiMotMat::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	if (this->timeDelay->delay(1000)) {
		isDungYen = !isDungYen;
	}
	
	if (isDungYen) {
		return;
	}
	int dtx = this->getMidX() - CPlayer::getInstance()->getPlayerHienTai()->getMidX();
	int dty = this->getMidY() - CPlayer::getInstance()->getPlayerHienTai()->getMidY();

	// trường hợp 1. nếu dtx xấp xỉ bằng 0 => đạn và xe đang có cùng toạ độ x, có thẻ khác toạ độ y. thì lúc này đạn bay dọc
	if (-1 < dtx && dtx < 1) {
		vx = 0;
		vy = dty > 0 ? -TOC_DO_MOT_MAT : TOC_DO_MOT_MAT;

		CGameObject::Update(dt);
		x += dx;
		y += dy;
		return;
	}

	// trường hợp 2. nếu dty xấp xỉ bằng 0 => đạn và xe đang có cùng toạ độ y, có thẻ khác toạ độ x. thì lúc này đạn bay ngang
	if (-1 < dty && dty < 1) {
		vy = 0;
		vx = dtx > 0 ? -TOC_DO_MOT_MAT : TOC_DO_MOT_MAT;

		CGameObject::Update(dt);
		x += dx;
		y += dy;
		return;
	}

	// công thức: vx/vy = dtx/dty => vx=dtx*vy/dty & vy=vx*dty/dtx;

	// nếu khoảng cách ngang lớn hơn khoảng cách dọc, ưu tiên cho vận tốc chiều ngang, nên gán vx 1 giá trị bất kỳ để tính vy. và ngược lại

	if (abs(dtx) > abs(dty)) {
		vx = dtx > 0 ? -TOC_DO_MOT_MAT : TOC_DO_MOT_MAT;
		vy = (dty * vx) / dtx;
		vy = dty > 0 ? -1 * abs(vy) : abs(vy);
	}
	else {
		vy = dty > 0 ? -TOC_DO_MOT_MAT : TOC_DO_MOT_MAT; // dty > 0 => đạn phía dưới xe, đạn cần bay lên => vy < 0;
		vx = (dtx * vy) / dty;
		vx = dtx > 0 ? -1 * abs(vx) : abs(vx);
	}
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void QuaiMotMat::Render() {
	if (isDungYen) {
		ani = 1;
	}
	else {
		ani = 0;
	}
	animation_set->at(ani)->Render(x, y);
}

void QuaiMotMat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 15;
}
