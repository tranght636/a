#include "Camera.h"
#include "CPlayer.h"
#include "QuanLyKhongGian.h"
#include "CongKhongGian.h"
#include "Portal.h"

Camera* Camera::instance = 0;
Camera* Camera::getInstance() {
	if (instance == 0) {
		instance = new Camera();
	}
	return instance;
}

float Camera::getX() {
	return x;
}

float Camera::getY() {
	return y;
}

float Camera::getLeft() {
	return x;
}
float Camera::getRight() {
	return x + width;
}
float Camera::getTop() {
	return y;
}
float Camera::getBottom() {
	return y + height;
}
float Camera::getMidY() {
	return y + height / 2;
}

void Camera::update() {
	switch (this->status)
	{
	case BINH_THUONG:
		this->xuLyBinhThuong();
		break;
	case CHUYEN_KHONG_GIAN:
		this->xuLyChuyenKhongGian();
		break;
	default:
		break;
	}
	
}

void Camera::xuLyChuyenKhongGian() {
	switch (this->huong)
	{
	case LOAD_MAP:
		CGame::GetInstance()->SwitchScene(1);
		break;
	case HUONG_QUA_PHAI:
		switch (this->loaiCong) {
			
		case 1:// cổng 1 // map chạy chiều ngang
			if (this->x < MAP_WIDTH) {
				this->x += TOC_DO_CHUYEN;
			}
			else if (this->x >= this->gioiHan) {
				this->x = this->gioiHan;
				this->status = BINH_THUONG;
				QuanLyKhongGian::getInstance()->setChuyenXong(true);
			}
			break;
		case 2: // cổng 6 // chuyển cổng 6 theo chiều dọc xuống
			if (this->x < this->gioiHan)
				this->x += TOC_DO_CHUYEN;
			else if (this->x >= this->gioiHan) {
				this->x = this->gioiHan;
				this->y += MAP_HEIGHT;
				this->status = BINH_THUONG;
				QuanLyKhongGian::getInstance()->setChuyenXong(true);
			}
			break;
		case 3: // các cổng còn lại
			if (this->x < this->gioiHan)
				this->x += TOC_DO_CHUYEN;
			else if (this->x >= this->gioiHan) {
				this->x = this->gioiHan;
				this->status = BINH_THUONG;
				QuanLyKhongGian::getInstance()->setChuyenXong(true);
			}
			break;
		case 7:// cổng 8// map chạy chiều dọc y giảm
			if (this->x < this->gioiHan)// loại 3
				this->x += TOC_DO_CHUYEN;
			else if (this->x >= this->gioiHan) {
				this->x = this->gioiHan;
				this->y -= MAP_HEIGHT;
				this->status = BINH_THUONG;
				QuanLyKhongGian::getInstance()->setChuyenXong(true);
			}
			break;
		}
		break;
	case HUONG_QUA_TRAI:
		switch (this->loaiCong) {
		case 4: // cổng 2 qua trái chạy theo chiều ngang x tăng
			if (this->x <= 10) {
				this->x = MAP_WIDTH;// giới hạn phải của map chuyển tới x+ w
			}
			if (this->getRight() > this->gioiHan + 16)
				this->x -= TOC_DO_CHUYEN;
			else if (this->getRight() <= this->gioiHan + 16) {
				this->x = this->gioiHan - this->width + 16;
				this->status = BINH_THUONG;
				QuanLyKhongGian::getInstance()->setChuyenXong(true);
			}
			break;
		case 5: // cổng 7 // qua trái theo diều dọc y giảm 
			if (this->getRight() > this->gioiHan + 16)// loại 3
				this->x -= TOC_DO_CHUYEN;
			else if (this->getRight() <= this->gioiHan + 16) {
				this->x = this->gioiHan - this->width + 16;
				this->y -= MAP_HEIGHT;
				this->status = BINH_THUONG;
				QuanLyKhongGian::getInstance()->setChuyenXong(true);
			}
			break;
		case 6: // các cổng còn lại
			if (this->getRight() > this->gioiHan + 16)
				this->x -= TOC_DO_CHUYEN;
			else if (this->getRight() <= this->gioiHan + 16) {
				this->x = this->gioiHan - this->width + 16;
				this->status = BINH_THUONG;
				QuanLyKhongGian::getInstance()->setChuyenXong(true);
			}
			break;
		case 8: // cổng 10// qua trái y thăng theo chiều dọc
			if (this->getRight() > this->gioiHan + 16)// loại 3
				this->x -= TOC_DO_CHUYEN;
			else if (this->getRight() <= this->gioiHan + 16) {
				this->x = this->gioiHan - this->width + 16;
				this->y += MAP_HEIGHT;
				this->status = BINH_THUONG;
				QuanLyKhongGian::getInstance()->setChuyenXong(true);
			}
			break;
		}
		break;
		
	case HUONG_LEN_TREN:
		if (this->getBottom() > this->gioiHan + 55)// loại 9
			this->y -= TOC_DO_CHUYEN;
		else if (this->getBottom() <= this->gioiHan + 55) {
			this->y = this->gioiHan - this->height + 55;
			this->status = BINH_THUONG;
			QuanLyKhongGian::getInstance()->setChuyenXong(true);
		}
		break;
	case HUONG_XUONG_DUOI:
		if (this->getTop() < this->gioiHan)// loại 9
			this->y += TOC_DO_CHUYEN;
		else if (this->getTop() >= this->gioiHan) {
			this->y = this->gioiHan;
			this->status = BINH_THUONG;
			QuanLyKhongGian::getInstance()->setChuyenXong(true);
		}
		break;
	case DICH_CHUYEN_TUC_THOI:
	
		if (this->x != 1562 && this->y != 802) {
			this->x = 1562;
			this->y = 802;
			this->status = BINH_THUONG;
			QuanLyKhongGian::getInstance()->setChuyenXong(true);
		}
		break;
	default:
		break;
	}
}


void Camera::xuLyBinhThuong() {
	
	CPlayer* player = CPlayer::getPlayerHienTai();
	float xPlayer = player->getMidX();
	float yPlayer = player->getY();

	float midYPlayer = player->getY() + 25;
	float midYCamera = this->getMidY();

	float vyPlayer = player->getVy();

	KhongGian* kg = QuanLyKhongGian::getInstance()->getKhongGianHienTai();
	
	// xử lý trục x
	float gioiHanPhai = kg->getRight() - SCREEN_WIDTH_1_2 - 16;
	float gioiHanTrai = kg->getLeft() + SCREEN_WIDTH_1_2;

	if (xPlayer > gioiHanTrai && xPlayer < gioiHanPhai) {//TileMap::getInstance()->getMapWidth() - SCREEN_DX - 16) {
		this->x = xPlayer - SCREEN_WIDTH_1_2;
	}

	// xử lý trục y
	if (this->height > kg->getHeight()) {
		return;
	}

	float gioiHanTren = kg->getTop() + 62;
	float gioiHanDuoi = kg->getBottom() - SCREEN_HEIGHT_1_2 + 46;
	if (yPlayer > gioiHanTren && yPlayer < gioiHanDuoi) {
		if (yPlayer - this->y < 60) {
			this->y = yPlayer - 60;
		}
		else if (yPlayer - this->y > 150) {
			this->y = yPlayer - 150;
		}
		
		
	}
}

void Camera::reset() {
	//this->x = 1025;
	this->x = 1025;
}

Camera::Camera()
{	
	//this->x = 1025;
	//this->y = 530;

	this->x = 1024;
	this->y = 1035;
	this->width = SCREEN_WIDTH;
	this->height = SCREEN_HEIGHT;
	this->status = BINH_THUONG;
}


Camera::~Camera()
{
}

void Camera::chuyenKhongGian(int huong, int gioiHan, int loaiCong) {
	this->huong = huong;
	this->gioiHan = gioiHan;
	this->status = CHUYEN_KHONG_GIAN;
	this->loaiCong = loaiCong;
}
