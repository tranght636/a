#include "QuaiVatBoRua.h"
#include "PlayerXe.h"

#define TOC_DO_BO_RUA 0.04f


QuaiVatBoRua::QuaiVatBoRua() : QuaiVat()
{
	this->width = 18;
	this->height = 18;
}


QuaiVatBoRua::~QuaiVatBoRua()
{
}

void QuaiVatBoRua::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	int dtx = this->getMidX() - CPlayer::getInstance()->getPlayerHienTai()->getMidX();
	int dty = this->getMidY() - CPlayer::getInstance()->getPlayerHienTai()->getMidY();

	if (!isDuocDiChuyen && abs(dtx) < 60 && abs(dty) < 60) {
		isDuocDiChuyen = true;
	}

	if (!isDuocDiChuyen) {
		return;
	}
	
	if (-1 < dtx && dtx < 1 && -1 < dty && dty < 1) {
		vx = 0;
		vy = 0;
		return;
	}

	// trường hợp 1. nếu dtx xấp xỉ bằng 0 => đạn và xe đang có cùng toạ độ x, có thẻ khác toạ độ y. thì lúc này đạn bay dọc
	if (-1 < dtx && dtx < 1) {
		vx = 0;
		vy = dty > 0 ? -TOC_DO_BO_RUA : TOC_DO_BO_RUA;

		CGameObject::Update(dt);
		x += dx;
		y += dy;
		return;
	}

	// trường hợp 2. nếu dty xấp xỉ bằng 0 => đạn và xe đang có cùng toạ độ y, có thẻ khác toạ độ x. thì lúc này đạn bay ngang
	if (-1 < dty && dty < 1) {
		vy = 0;
		vx = dtx > 0 ? -TOC_DO_BO_RUA : TOC_DO_BO_RUA;

		CGameObject::Update(dt);
		x += dx;
		y += dy;
		return;
	}

	// công thức: vx/vy = dtx/dty => vx=dtx*vy/dty & vy=vx*dty/dtx;

	// nếu khoảng cách ngang lớn hơn khoảng cách dọc, ưu tiên cho vận tốc chiều ngang, nên gán vx 1 giá trị bất kỳ để tính vy. và ngược lại

	if (abs(dtx) > abs(dty)) {
		vx = dtx > 0 ? -TOC_DO_BO_RUA : TOC_DO_BO_RUA;
		vy = (dty * vx) / dtx;
		vy = dty > 0 ? -1 * abs(vy) : abs(vy);
	}
	else {
		vy = dty > 0 ? -TOC_DO_BO_RUA : TOC_DO_BO_RUA; // dty > 0 => đạn phía dưới xe, đạn cần bay lên => vy < 0;
		vx = (dtx * vy) / dty;
		vx = dtx > 0 ? -1 * abs(vx) : abs(vx);
	}


	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void QuaiVatBoRua::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void QuaiVatBoRua::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 1;
	top = y + 1;
	right = x + 18;
	bottom = y + 18;
}
