#include "DanOfQuaiVatDauSau.h"
#include "PlayerXe.h"
#include "Brick.h"
#include "CPlayer.h"
#include "PlayerNguoi.h"

DanOfQuaiVatDauSau::DanOfQuaiVatDauSau()
{
	this->ani = 0;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANI_DAN_OF_QUAI_VAT_DAU_SAU));

	
}

void DanOfQuaiVatDauSau::setV() {
	int dtx = x - CPlayer::getInstance()->getPlayerHienTai()->getMidX();
	int dty = y - CPlayer::getInstance()->getPlayerHienTai()->getMidY();
	// trường hợp 1. nếu dtx xấp xỉ bằng 0 => đạn và xe đang có cùng toạ độ x, có thẻ khác toạ độ y. thì lúc này đạn bay dọc
	if (-1 < dtx && dtx < 1) {
		vx = 0;
		vy = 0.1f;
		return;
	}

	// trường hợp 2. nếu dty xấp xỉ bằng 0 => đạn và xe đang có cùng toạ độ y, có thẻ khác toạ độ x. thì lúc này đạn bay ngang
	if (-1 < dty && dty < 1) {
		vy = 0;
		vx = 0.1f;
		return;
	}

	// công thức: vx/vy = dtx/dty => vx=dtx*vy/dty & vy=vx*dty/dtx;

	// nếu khoảng cách ngang lớn hơn khoảng cách dọc, ưu tiên cho vận tốc chiều ngang, nên gán vx 1 giá trị bất kỳ để tính vy. và ngược lại
	if (abs(dtx) > abs(dty)) {
		vx = dtx > 0 ? -0.1f : 0.1f;
		vy = (dty * vx) / dtx;
		vy = dty > 0 ? -1 * abs(vy) : abs(vy);
	}
	else {
		vy = dty > 0 ? -0.1f : 0.1f; // dty > 0 => đạn phía dưới xe, đạn cần bay lên => vy < 0;
		vx = (dtx * vy) / dty;
		vx = dtx > 0 ? -1 * abs(vx) : abs(vx);
	}
}

DanOfQuaiVatDauSau::~DanOfQuaiVatDauSau()
{
}

void DanOfQuaiVatDauSau::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// Lọc brick,
	vector<LPGAMEOBJECT> objectFilter;
	filterCoObject(&objectFilter, coObjects);

	CGameObject::Update(dt);

	// Lấy danh sách va chạm với Player
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(&objectFilter, coEvents);

	// Xử lý bình thường
	if (coEvents.size() == 0) {

		x += dx;
		y += dy;
		return;
	}
	if (coEvents.size() != 0) {
		float min_tx, min_ty, nx = 0, ny;
		vector<LPCOLLISIONEVENT> coEventsResult;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// Lấy từng object để xử lý
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Brick*>(e->obj)) {
				this->ani = 1;
				this->release(); 
			}
		}


	}
}

void DanOfQuaiVatDauSau::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void DanOfQuaiVatDauSau::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 1;
	top = y + 1;
	right = x + 3;
	bottom = y + 3;
}
void DanOfQuaiVatDauSau::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
	// Lấy từng object để xử lý
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Brick*>(coObjects->at(i))) // Nếu va chạm với đất
		{
			kq->push_back(coObjects->at(i));
		}
	}
}