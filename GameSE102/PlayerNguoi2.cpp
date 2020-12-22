#include "PlayerNguoi2.h"
#include "CSampleKeyHandler.h"
#include "Portal.h"
#include "PlayerNguoi.h"
#include "QuanLyKhongGian.h"
#include "CongKhongGian.h"
#include "VatPham.h"
#include "VienDanPlayerNguoi2.h"
#include "PlayScence.h"

PlayerNguoi2::PlayerNguoi2()
{
	this->ani = 0;
	this->width = 8;
	this->isNhay = false;
	this->mau = MAU;
}

PlayerNguoi2::~PlayerNguoi2()
{
}

int khongGianIdN2;
int huongN2;
int loaiCongN2;

PlayerNguoi2* PlayerNguoi2::instance = NULL;
PlayerNguoi2* PlayerNguoi2::getInstance() {
	if (instance == NULL) {
		instance = new PlayerNguoi2();
	}
	return instance;
}

void PlayerNguoi2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	switch (this->status)
	{
	case PLAYER_NGUOI2_STATUS_BINH_THUONG:
		this->xuLyBinhThuong(dt, coObjects);
		break;
	case STATUS_CHUYEN_KHONG_GIAN:
		this->xyLyChuyenKhongGian();
		break;
	case STATUS_BAN:
		this->xuLyBan();
		break;
	default:
		break;
	}
}


void PlayerNguoi2::Render()
{
	animation_set->at(ani)->Render(x, y, !isDirRight);
	//RenderBoundingBox(150);
}


void PlayerNguoi2::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y+15;
	right = x + 15;	// getAnimation(animationIndex)->getFrame(frameIndex)->getWidth();
	bottom = y + 30; // ||||||||
}

void PlayerNguoi2::xuLyBinhThuong(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// Xử lý phím vx
	CSampleKeyHandler::update();

	if (CSampleKeyHandler::isRightDown) {
		this->vx = PLAYER_NGUOI_WALKING_SPEED;
		this->isDirRight = true;
		this->ani = PLAYER_NGUOI2_ANI_DI_CHUYEN_TRAI_PHAI;
		huong = 1;
	}
	else if (CSampleKeyHandler::isLeftDown) {
		this->vx = -PLAYER_NGUOI_WALKING_SPEED;
		this->isDirRight = false;
		this->ani = PLAYER_NGUOI2_ANI_DI_CHUYEN_TRAI_PHAI;
		huong = 2;
	}
	else {
		this->vx = 0;
		isLastAni = this->ani;
		if (isLastAni == PLAYER_NGUOI2_ANI_DI_CHUYEN_TRAI_PHAI) {
			this->ani = PLAYER_NGUOI2_ANI_DUNG_YEN_TRAI_PHAI;
		}
	}
	if (CSampleKeyHandler::isDownDown) {
		this->vy = PLAYER_NGUOI_WALKING_SPEED;
		this->ani = PLAYER_NGUOI2_ANI_DI_CHUYEN_XUONG;
		huong = 3;
	}
	else if (CSampleKeyHandler::isUpDown) {
		this->vy = -PLAYER_NGUOI_WALKING_SPEED;
		this->ani = PLAYER_NGUOI2_ANI_DI_CHUYEN_LEN;
		huong = 4;
	}
	else {
		this->vy = 0;
		isLastAni = this->ani;
		 if (isLastAni == PLAYER_NGUOI2_ANI_DI_CHUYEN_LEN) {
			this->ani = PLAYER_NGUOI2_ANI_DUNG_YEN_LEN;
		}
		else if (isLastAni == PLAYER_NGUOI2_ANI_DI_CHUYEN_XUONG) {
			this->ani = PLAYER_NGUOI2_ANI_DUNG_YEN_XUONG;
		}
	}
	

	// Calculate dx, dy 
	CGameObject::Update(dt);
	

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
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

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
					this->isNhay = false;
				}
			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);

				// do game có 2 cảnh nên không cần check cổng
				CPlayer::setPlayerHienTai(PLAYER_NGUOI);

				Camera* cam = Camera::getInstance();
				cam->setX(cam->getXHienTai());
				cam->setY(cam->getYHienTai());
				QuanLyKhongGian::getInstance()->setKhongGianHienTaiId(PlayerNguoi::getInstance()->getKgHienTai());
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
				break;
			}
			else if (dynamic_cast<CongKhongGian*>(e->obj))
			{
				if (this->status == BINH_THUONG) {
					this->status = CHUYEN_KHONG_GIAN;
				}
				CongKhongGian* ckg = dynamic_cast<CongKhongGian*>(e->obj);
				khongGianIdN2 = ckg->getKhongGianId();
				huongN2 = ckg->getHuong();
				this->start_x = ckg->getXPlayer();
				this->start_y = ckg->getYPlayer();
				loaiCongN2 = ckg->getLoaiCong();
				break;
			}
			else if (dynamic_cast<VatPham*>(e->obj)) {
				// cong mau hoac do manh cua dan
				VatPham* vp = dynamic_cast<VatPham*>(e->obj);
				vp->release();
			}

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void PlayerNguoi2::xyLyChuyenKhongGian() {
	// TO-DO: tự di chuyển player đến khi biến mất.

	this->y = -50;

	if (QuanLyKhongGian::getInstance()->getChuyenXong()) {
		QuanLyKhongGian::getInstance()->chuyenKhongGian(khongGianIdN2, huongN2, loaiCongN2);
	}
	if (this->status == CHUYEN_KHONG_GIAN && QuanLyKhongGian::getInstance()->getChuyenXong()) {
		this->status = BINH_THUONG;
		this->x = this->start_x;
		this->y = this->start_y;
	}

	// TO-DO: cho player xuất hiện trở lại, status -> bình thường
}
void PlayerNguoi2::xuLyBan() {
	if (this->is90) {
		VienDanPlayerNguoi2* vienDan = new VienDanPlayerNguoi2();
		vienDan->setX(this->x +7);
		vienDan->setY(this->y +15);
		CPlayScene::addObjectToGrid(vienDan);
	}
	else {
		bool isDirRight = this->isDirRight;
		VienDanPlayerNguoi2* vienDan = new VienDanPlayerNguoi2(huong);
		vienDan->setX(this->x+7);
		vienDan->setY(this->y+15);

		CPlayScene::addObjectToGrid(vienDan);

	}
	this->status = PLAYER_NGUOI2_STATUS_BINH_THUONG;
}

void PlayerNguoi2::xuLyChet() {
}
