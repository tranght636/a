#include "PlayerXe.h"
#include "CPLayer.h"
#include "CSampleKeyHandler.h"
#include "QuaiVat.h"
#include "QuanLyKhongGian.h"
#include "CongKhongGian.h"
#include "VienDan1Trai.h"
#include "PlayScence.h"
#include "Utils.h"
#include "VienDan1Len.h"
#include "DanOfQuai.h"
#include "VatPham.h"
#include "VatPhamP.h"

PlayerXe::PlayerXe() {
	this->ani = 0;
	this->isDirRight = true;
	this->isDuocNhayCao = true;
	this->width = 26;
	this->height = 15;
	this->status = BINH_THUONG;
	this->mau = MAU;
}

PlayerXe::~PlayerXe() {

}


int khongGianId;
int huong;
int loaiCong;

PlayerXe* PlayerXe::instance = NULL;
PlayerXe* PlayerXe::getInstance() {
	if (instance == NULL) {
		instance = new PlayerXe();
	}
	return instance;
}

void PlayerXe::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	switch (this->status)
	{
	case STATUS_BINH_THUONG:
		this->xuLyTrangThaiBinhThuong(dt, coObjects);
		break;
	case STATUS_CHUYEN_KHONG_GIAN:
		this->xyLyChuyenKhongGian();
		break;
	case STATUS_BAN:
		//this->xuLyBan();
		this->xuLyBan(dt, coObjects);
		break;
	case STATUS_CHET:
		this->xuLyChet();
		break;
	default:
		break;
	}
}

void PlayerXe::Render()
{
	if (this->isStartQuayDau) {
		animation_set->at(PLAYER_XE_ANI_QUAY_DAU)->Render(x, y, isDirRight);
		if (delay(PLAYER_XE_TIME_QUAY_DAU)) {
			this->isStartQuayDau = false;
		}
		return;
	}

	if (this->ani == PLAYER_XE_CHUYEN_PLAYER) {
		if (delay(1000) || this->isDangChet) {
			this->ani = PLAYER_XE_ANI_DUNG_YEN;
		}
	}
	
	if (this->isDangChet) {
		if (delay(50)) {
			this->alpha = this->alpha == 180 ? 80 : 180;
		}
	}
	else {
		this->alpha = 255;
	}
	animation_set->at(ani)->Render(x, y, isDirRight, this->alpha);
	//RenderBoundingBox(150);
}


void PlayerXe::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + 26;
	bottom = y + 15;
}

// Viết mới

void PlayerXe::xuLyTrangThaiBinhThuong(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (this->mau <= 0)
	{
		this->status = STATUS_CHET;
		return;
	}
	// Xử lý phím vx
	CSampleKeyHandler::update();

	if (GetAsyncKeyState(VK_UP) || delayPhim(150, GetAsyncKeyState(VK_UP))) {
		if (this->is90 || delayPhim(150, GetAsyncKeyState(VK_UP))) {
			this->is90 = true;
			this->ani = PLAYER_XE_BAN_90_DUNG_YEN;
		}
		else
		{
			this->ani = PLAYER_XE_BAN_45_DUNG_YEN;
		}
		if (CSampleKeyHandler::isRightDown) {
			this->vx = PLAYER_XE_WALKING_SPEED;
			this->isDirRight = true;
			this->ani = PLAYER_XE_BAN_90_DI_CHUYEN;
		}
		else if (CSampleKeyHandler::isLeftDown) {
			this->vx = -PLAYER_XE_WALKING_SPEED;
			this->isDirRight = false;
			this->ani = PLAYER_XE_BAN_90_DI_CHUYEN;
		}
		else {
			this->vx = 0;
		}
	}

	else if (CSampleKeyHandler::isRightDown) {
		this->vx = PLAYER_XE_WALKING_SPEED;
		if (!this->isDirRight) {
			this->isStartQuayDau = true;
			this->isDirRight = true;
		}
		else if (!this->isNhay && this->vy < 0) {
			this->ani = PLAYER_XE_NHAY_DI_CHUYEN;
		}
		else {
			this->ani = PLAYER_XE_ANI_CHAY;
		}

		this->is90 = false;
	}
	else if (CSampleKeyHandler::isLeftDown) {
		this->vx = -PLAYER_XE_WALKING_SPEED;
		if (this->isDirRight) {
			this->isStartQuayDau = true;
			this->isDirRight = false;
		}
		else if (!this->isNhay && this->vy < 0) {
			this->ani = PLAYER_XE_NHAY_DI_CHUYEN;
		}
		else{
			this->ani = PLAYER_XE_ANI_CHAY;
		}

		this->is90 = false;
	}
	else {
		this->vx = 0;
		if (!this->isNhay && this->vy < 0) {
			this->ani = PLAYER_XE_NHAY_DUNG_YEN;
		}
		else {
			this->ani = PLAYER_XE_ANI_DUNG_YEN;
		}
		
		this->is90 = false;
	}

	// Xử lý phím vy
	// Bấm phím 'x' trên mặt đất thì mới được nhảy
	// Nếu giữ phím 'x' thì nhảy cao hơn
	if (this->isNhay && CSampleKeyHandler::isXDown) {

		this->isNhay = false;

		this->vy = -PLAYER_XE_JUMP_SPEED_Y;
		CSampleKeyHandler::isXDown = false;
	}
	bool xState = GetAsyncKeyState('X');

	if (!this->isNhay
		&& this->vy > -0.1f
		&& this->vy < 0
		&& this->isDuocNhayCao
		&& xState) {

		this->isDuocNhayCao = false;

		this->vy = -0.15f;
	}

	// Calculate dx, dy 
	CGameObject::Update(dt);
	// Xử lý rớt
	this->vy += PLAYER_XE_GRAVITY * dt;

	if (this->isDangChet) {
		if(this->timeDelay->delay(TIME_DANG_CHET)) {
			this->isDangChet = false;
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) // Nếu không có va chạm, xử lý bình thường
	{
		// chặn trái
		if (vx < 0 && x < 0) {
			vx = 0;
			x = 0;
		}
		// chặn phải
		else if (vx > 0 && x > TileMap::getInstance()->getMapWidth() - 16) {
			vx = 0;
			x = TileMap::getInstance()->getMapWidth() - 16;
		}
		else {
			x += dx;
		}

		// chặn trên
		if (vy < 0 && y < 0) {
			vy = 0;
			y = 0;
		}
		else {
			y += dy;
		}
	}
	else	// nếu có va chạm
	{
		float min_tx, min_ty, nx = 0, ny;

		// Lấy danh sách va chạm với Player
		vector<LPCOLLISIONEVENT> coEventsResult;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.1f;
		y += min_ty * dy + ny * 0.1f;

		if (nx != 0) vx = 0;	// không cho đi khi xảy ra va chạm
		if (ny != 0) vy = 0;

		// Lấy từng object để xử lý
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Brick*>(e->obj)) // Nếu va chạm với đất
			{
				
				Brick* brick = dynamic_cast<Brick*>(e->obj);
				if (e->ny < 0)	//ny < 0 đáy player chạm trên của đất
				{
					this->isNhay = true;
					this->isDuocNhayCao = true;
				}
			}

			else if (dynamic_cast<QuaiVat*>(e->obj)) {
				y +=-abs( min_ty * dy + ny * 0.1f);
				if (dynamic_cast<DanOfQuai*>(e->obj)) {
					DanOfQuai* doq = dynamic_cast<DanOfQuai*>(e->obj);
					doq->release();
				}
				if (!this->isDangChet) {
					//this->truMau();
					this->isDangChet = true;
				}
			}
			
			else if (dynamic_cast<CongKhongGian*>(e->obj))
			{
				if (this->status == BINH_THUONG) {
					this->status = CHUYEN_KHONG_GIAN;
				}
				CongKhongGian* ckg = dynamic_cast<CongKhongGian*>(e->obj);
				khongGianId = ckg->getKhongGianId();
				huong = ckg->getHuong();
				this->start_x = ckg->getXPlayer();
				this->start_y = ckg->getYPlayer();
				loaiCong = ckg->getLoaiCong();
				break;
			}
			else if (dynamic_cast<VatPham*>(e->obj)) {
				// cong mau hoac do manh cua dan
				VatPham* vp = dynamic_cast<VatPham*>(e->obj);
				if (dynamic_cast<VatPhamP*>(e->obj)) {
					this->themMau();
				}
				vp->release();
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void PlayerXe::xyLyChuyenKhongGian() {
	// TO-DO: tự di chuyển player đến khi biến mất.

	this->y = -50;

	if (QuanLyKhongGian::getInstance()->getChuyenXong()) {
		QuanLyKhongGian::getInstance()->chuyenKhongGian(khongGianId, huong, loaiCong);
	}
	if (this->status == CHUYEN_KHONG_GIAN && QuanLyKhongGian::getInstance()->getChuyenXong()) {
		this->status = BINH_THUONG;
		this->x = this->start_x;
		this->y = this->start_y;
	}

	// TO-DO: cho player xuất hiện trở lại, status -> bình thường
}

//void PlayerXe::xuLyBan() {
//	// 1 lan chi duoc ban 4 vien
//	
//	if (this->is90) {
//		VienDan1Len* vienDan = new VienDan1Len();
//		vienDan->setX(this->x + (this->isDirRight ? 4 : 8));
//		vienDan->setY(this->y - 15);
//		CPlayScene::addObjectToGrid(vienDan);
//	}
//	else {
//		bool isDirRight = this->isDirRight;
//		VienDan1Trai* vienDan = new VienDan1Trai(isDirRight);
//		vienDan->setX(this->x);
//		vienDan->setY(this->y);
//
//		CPlayScene::addObjectToGrid(vienDan);
//
//	}
//	this->status = STATUS_BINH_THUONG;
//}
void PlayerXe::xuLyBan(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// 1 lan chi duoc ban 4 vien
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	vector<LPGAMEOBJECT> objectFilter;
	filterCoObject(&objectFilter, coObjects);
	CalcPotentialCollisions(&objectFilter, coEvents);
	float min_tx, min_ty, nx = 0, ny;
	vector<LPCOLLISIONEVENT> coEventsResult;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	if (objectFilter.size() >=3) {

		return;
	}

	if (this->is90) {
		VienDan1Len* vienDan = new VienDan1Len();
		vienDan->setX(this->x + (this->isDirRight ? 4 : 8));
		vienDan->setY(this->y - 15);
		CPlayScene::addObjectToGrid(vienDan);
	}
	else {
		bool isDirRight = this->isDirRight;
		VienDan1Trai* vienDan = new VienDan1Trai(isDirRight);
		vienDan->setX(this->x);
		vienDan->setY(this->y);

		CPlayScene::addObjectToGrid(vienDan);

	}
	this->status = STATUS_BINH_THUONG;
}

void PlayerXe::xuLyChet() {
	this->ani = PLAYER_XE_ANI_NO;
	if (this->timeDelay->delay(100)) {
		CGame::GetInstance()->loadSceneWhenPlayerDie();
	}
}
void PlayerXe::filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects) {
	// Lấy từng object để xử lý
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<VienDan1Trai*>(coObjects->at(i)) ||dynamic_cast<VienDan1Len*>(coObjects->at(i))) // Nếu va chạm với đất
		{
			kq->push_back(coObjects->at(i));
		}
	}
}