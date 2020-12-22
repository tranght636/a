#include "PlayerNguoi.h"
#include "CSampleKeyHandler.h"
#include "Portal.h"
#include "PlayerNguoi2.h"
#include "QuanLyKhongGian.h"
#include "VienDanPlayerNguoi.h"
#include "PlayScence.h"
#include "VatPham.h"

PlayerNguoi::PlayerNguoi()
{
	this->ani = PLAYER_NGUOI_ANI_DI_CHUYEN;
	this->width = 8;
	this->isNhay = false;
	this->mau = MAU;

}

PlayerNguoi::~PlayerNguoi()
{
}

PlayerNguoi* PlayerNguoi::instance = NULL;
PlayerNguoi* PlayerNguoi::getInstance() {
	if (instance == NULL) {
		instance = new PlayerNguoi();
	}
	return instance;
}

void PlayerNguoi::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	switch (this->status)
	{
	case PLAYER_NGUOI_STATUS_BINH_THUONG:
		this->xuLyBinhThuong(dt, coObjects);
		break;
	case PLAYER_NGUOI_STATUS_DI_THANG:
		this->xuLyDiThang(dt, coObjects);
		break;
	case STATUS_BAN:
		this->xuLyBan();
		break;
	default:
		break;
	}
}

void PlayerNguoi::Render()
{
	animation_set->at(ani)->Render(x, y, !isDirRight);
	//RenderBoundingBox(150);
}


void PlayerNguoi::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + 8;	// getAnimation(animationIndex)->getFrame(frameIndex)->getWidth();
	bottom = y + 16; // ||||||||
}

void PlayerNguoi::xuLyBinhThuong(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	// Xử lý phím vx
	CSampleKeyHandler::update();

	if (CSampleKeyHandler::isRightDown) {
		this->vx = PLAYER_NGUOI_WALKING_SPEED;
		this->isDirRight = true;
		this->ani = PLAYER_NGUOI_ANI_DI_CHUYEN;
		huong = 1;
	}
	else if (CSampleKeyHandler::isLeftDown) {
		this->vx = -PLAYER_NGUOI_WALKING_SPEED;
		this->isDirRight = false;
		this->ani = PLAYER_NGUOI_ANI_DI_CHUYEN;
		huong = 2;
	}
	else {
		this->vx = 0;
		this->ani = PLAYER_NGUOI_ANI_DUNG_YEN;
	}

	// xử lý nhảy
	if (CSampleKeyHandler::isXDown && !this->isNhay) {
		this->vy = -PLAYER_NGUOI_JUMP_SPEED_Y;
		this->isNhay = true;
		CSampleKeyHandler::isXDown = false;
		this->ani = PLAYER_NGUOI_ANI_DUNG_YEN;

	}

	// Calculate dx, dy 
	CGameObject::Update(dt);
	// Xử lý rớt
	this->vy += PLAYER_NGUOI_GRAVITY * dt;

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
				if (e->ny != 0) {
					continue;
				}
				CPortal* p = dynamic_cast<CPortal*>(e->obj);

				// do game có 2 cảnh nên không cần check cổng
				CPlayer::setPlayerHienTai(PLAYER_NGUOI_2);
				Camera* cam = Camera::getInstance();
				cam->saveViTriHienTai(cam->getX(), cam->getY());

				cam->setX(p->getXCam());
				cam->setY(p->getYCam());
				PlayerNguoi2::getInstance()->setX(p->getXPlayer());
				PlayerNguoi2::getInstance()->setY(p->getYPlayer());
				                             // lưu vết ...
				this->khongGianIdHienTai = QuanLyKhongGian::getInstance()->getKhongGianHienTaiId();
				
				QuanLyKhongGian::getInstance()->setKhongGianHienTaiId(p->getKhongGianId());

				CGame::GetInstance()->SwitchScene(p->GetSceneId());
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

void PlayerNguoi::xuLyDiThang(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CSampleKeyHandler::update();

	if (CSampleKeyHandler::isUpDown && this->y>395) {
		this->vy = -0.05f;
		this->ani = PLAYER_NGUOI_ANI_LEO_THANG;

	}
	else if (CSampleKeyHandler::isDownDown) {
		this->vy = 0.05f;
		this->hetThang = false;
		this->ani = PLAYER_NGUOI_ANI_LEO_THANG;

	}
	else {
		this->vy = 0;
		this->ani = PLAYER_NGUOI_ANI_LEO_THANG_DUNG;
	}

	// Tính dx, dy 
	CGameObject::Update(dt);
	y += dy;

}
void PlayerNguoi::xuLyBan() {
		VienDanPlayerNguoi* vienDan = new VienDanPlayerNguoi(huong);
		vienDan->setX(this->x + 3);
		vienDan->setY(this->y + 10);
		CPlayScene::addObjectToGrid(vienDan);
		this->status = PLAYER_NGUOI2_STATUS_BINH_THUONG;
}


void PlayerNguoi::xuLyChet() {

}
