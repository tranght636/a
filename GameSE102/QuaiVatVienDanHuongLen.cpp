#include "QuaiVatVienDanHuongLen.h"
#include "PlayerXe.h"
#include "Brick.h"
#include "CPlayer.h"
#include "PlayerNguoi.h"

#define VY_QUAI_VAT_VIEN_DAN_HUONG_LEN 0.05
#define VX_QUAI_VAT_VIEN_DAN_HUONG_LEN 0.05
#define V_TAN_CONG	0.1


QuaiVatVienDanHuongLen::QuaiVatVienDanHuongLen() : QuaiVat()
{
	this->vx = VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
	this->vy = VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
	vxDiChuyen = vx;
	vyDiChuyen = vy;

}


QuaiVatVienDanHuongLen::~QuaiVatVienDanHuongLen()
{
}
/*

	this->ani = 0;
	if (this->loai == 1) {
		if (this->x <= this->gioiHanTrai || this->x >= this->gioiHanPhai) {
			this->vx *= -1;
			this->x += vx > 0 ? 5 : -5;
		}
		CGameObject::Update(dt);
		this->vy = 0.15f;


		// Lọc brick,
		vector<LPGAMEOBJECT> objectFilter;
		filterCoObject(&objectFilter, coObjects);

		// Lấy danh sách va chạm với Player
		vector<LPCOLLISIONEVENT> coEvents;
		coEvents.clear();
		CalcPotentialCollisions(&objectFilter, coEvents);

		// Xử lý bình thường
		if (coEvents.size() == 0) {
			this->y += dy;
			return;
		}
		else {
			float min_tx, min_ty, nx = 0, ny;
			vector<LPCOLLISIONEVENT> coEventsResult;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// Lấy từng object để xử lý
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<Brick*>(e->obj)) // Nếu va chạm với đất
				{
					Brick* brick = dynamic_cast<Brick*>(e->obj);
					if (e->ny < 0)	//ny < 0 đáy player chạm trên của đất
					{
						vy = 0;
						y += min_ty * dy + ny * 0.1f;
					}
					this->x += dx;
				}
			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else if (this->loai == 2) {
		this->ani = 1;
		if (this->start_x <= PlayerXe::getInstance()->getX()+16 && this->start_x >= PlayerXe::getInstance()->getX()){
			this->move = true;
		}
		if (this->move) {
			if (this->x <= this->gioiHanTrai || this->x >= this->gioiHanPhai) {
				this->vx *= -1;
				this->x += vx > 0 ? 5 : -5;
			}
			CGameObject::Update(dt);
			this->vy = 0.15f;


			// Lọc brick,
			vector<LPGAMEOBJECT> objectFilter;
			filterCoObject(&objectFilter, coObjects);

			// Lấy danh sách va chạm với Player
			vector<LPCOLLISIONEVENT> coEvents;
			coEvents.clear();
			CalcPotentialCollisions(&objectFilter, coEvents);

			// Xử lý bình thường
			if (coEvents.size() == 0) {
				// Con sâu luôn rớt xuống
				this->ani = 2;
				this->y += dy;
				return;
			}
			else {
				this->loai = 1;

			}

			// clean up collision events
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}
		else {

			if (this->y <= 1056 || this->y >= 1102) {
				this->vy *= -1;
				this->y += vy > 0 ? 5 : -5;
			}
			CGameObject::Update(dt);
			this->y += this->dy;
		}


	}
*/

void QuaiVatVienDanHuongLen::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vector<LPGAMEOBJECT> objectFilter;
	filterCoObject(&objectFilter, coObjects);
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(&objectFilter, coEvents);
	if (tanCong) {
		y += dy;
		x += dx;
	}
	if (!tanCong && coEvents.size() == 0 ) {
		if (diChuyen == 0) {
			if (ani == 0 || ani == 2) {
				y += dy;
			}
			else if (ani == 1 || ani == 3) {
				x += dx;
			}
		}
		else if (diChuyen == 2) {
			if (ani == 0 ) {
				if (vx > 0) {
					this->x += 3;
					this->y += 3;
					ani = 3;
					vx = -VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vy = VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
				}
				else {
					this->x -= 3;
					this->y += 3;
					ani = 1;
					vx = VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vy = VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
				}
				
				diChuyen = 0;
			}
			else if (ani == 3) {
				if (vy > 0) {
					this->x -= 3;
					this->y += 3;
					ani = 2;
					vy = -VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vx = -VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
				}
				else {
					this->x -= 3;
					this->y -= 3;
					ani = 0;
					vy = VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vx = -VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
				}
				
				diChuyen = 0;
			}
			else if (ani == 2) {
				if (vx < 0) {
					this->x -= 3;
					this->y -= 3;
					ani = 1;
					vx = VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vy = -VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
				}
				else {
					this->x += 3;
					this->y -= 3;
					ani = 3;
					vx = -VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vy = -VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
				}
				diChuyen = 0;
			}
			else if (ani == 1 ) {
				if (vy < 0) {
					this->x += 3;
					this->y -= 3;
					ani = 0;
					vy = VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vx = VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
				}
				else {
					this->x += 3;
					this->y += 3;
					ani = 2;
					vy = -VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vx = VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
				}
				
				diChuyen = 0;
			}
		}
	}
	else if (coEvents.size() != 0) {
		if (tanCong) {
			if (ani == 2) {
				ani = 0;
				y -= 3;
				vx = vxDiChuyen;
				vy = -vyDiChuyen;
			}
			else if (ani == 0) {
				ani = 2;
				y += 3;
				vx = vxDiChuyen;
				vy = -vyDiChuyen;
			}
			else if (ani == 1) {
				ani = 3;
				x += 3;
				vx = -vxDiChuyen;
				vy = vyDiChuyen;
			}
			else if (ani == 3) {
				ani == 1;
				x -= 3;
				vx = vxDiChuyen;
				vy = vyDiChuyen;
			}
			diChuyen = 0;
			tanCong = false;
		}

		// tan cong
		int dtx = x - CPlayer::getInstance()->getPlayerHienTai()->getMidX();
		int dty = y - CPlayer::getInstance()->getPlayerHienTai()->getMidY();

		if (abs(dtx) < 2) {
			if (ani == 2 && dty < 0) {
				vxDiChuyen = vx;
				vyDiChuyen = vy;
				vy = V_TAN_CONG;
				vx = 0;
				tanCong = true;
			}
			else if (ani == 0 && dty > 0) {
				vxDiChuyen = vx;
				vyDiChuyen = vy;
				vy = -V_TAN_CONG;
				vx = 0;
				tanCong = true;
			}
		}if (abs(dty) < 2) {
			if (ani == 1 && dtx > 0) {
				vxDiChuyen = vx;
				vyDiChuyen = vy;
				vx = -V_TAN_CONG;
				vy = 0;
				tanCong = true;
			}
			else if (ani == 3 && dtx < 0) {
				vxDiChuyen = vx;
				vyDiChuyen = vy;
				vx = V_TAN_CONG;
				vy = 0;
				tanCong = true;
			}
		}

		if (coEvents.size() == 1) {
			if (ani == 0 || ani == 2) {
				x += dx;
			}
			else if (ani == 1 || ani == 3) {
				y += dy;
			}
			diChuyen = 2;
		}
		else if (coEvents.size() > 1) {
			if (ani == 0) {
				if (vx > 0) {
					ani = 1;
					x -= 5;
					y -= 5;
					vy = -VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vx = VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					diChuyen = 0;
				}
				else {
					ani = 3;
					x += 3;
					y -= 3;
					vy = -VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vx = -VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					diChuyen = 0;
				}
			}
			else if (ani == 1) {
				if (vx > 0) {
					ani = 2;
					x -= 3;
					y += 3;
					vy = -VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vx = -VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					diChuyen = 0;
				}
				else {
					ani = 2;
					x += 3;
					y += 3;
					vy = -VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vx = VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					diChuyen = 0;
				}
			}
			else if (ani == 2) {
				if (vx < 0) {
					ani = 3;
					x += 3;
					y += 3;
					vy = VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vx = -VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					diChuyen = 0;
				}
				else {
					ani = 1;
					x -= 3;
					y += 3;
					vy = VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vx = VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					diChuyen = 0;
				}
			}
			else if (ani == 3) {
				if (vy > 0) {
					ani = 0;
					x += 3;
					y -= 3;
					vy = VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vx = VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					diChuyen = 0;
				}
				else {
					ani = 0;
					x -= 3;
					y += 3;
					vy = VY_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					vx = -VX_QUAI_VAT_VIEN_DAN_HUONG_LEN;
					diChuyen = 0;
				}
			}
		}
	}




}
void QuaiVatVienDanHuongLen::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
	// Lấy từng object để xử lý
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Brick*>(coObjects->at(i))) // Nếu va chạm với đất
		{
			kq->push_back(coObjects->at(i));
		}
	}
}

void QuaiVatVienDanHuongLen::Render() {
	animation_set->at(ani)->Render(x, y);
}

void QuaiVatVienDanHuongLen::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 19;
	bottom = y + 16;
}
