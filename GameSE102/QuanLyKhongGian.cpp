#include "QuanLyKhongGian.h"
#include "Camera.h"


QuanLyKhongGian::QuanLyKhongGian()
{
	this->khongGianHienTai = 1;
	this->chuyenXong = true;
}


QuanLyKhongGian::~QuanLyKhongGian()
{
}


QuanLyKhongGian* QuanLyKhongGian::instance = NULL;

QuanLyKhongGian* QuanLyKhongGian::getInstance() {
	if (instance == NULL) {
		instance = new QuanLyKhongGian();
	}
	return instance;
}

void QuanLyKhongGian::addKhongGian(KhongGian* kg) {
	this->dsKhongGian[kg->getId()] = kg;
}

KhongGian* QuanLyKhongGian::getKhongGian(int id) {
	return this->dsKhongGian[id];
}

KhongGian* QuanLyKhongGian::getKhongGianHienTai() {
	return this->dsKhongGian[khongGianHienTai];
}


void QuanLyKhongGian::chuyenKhongGian(int id, int huong, int loaiCong) {
	if (this->khongGianHienTai == id) {
		return;
	}

	this->khongGianHienTai = id;
	this->chuyenXong = false;

	KhongGian* kg = dsKhongGian[id];
	
	Camera* camera = Camera::getInstance();
	float gioiHan = 1;
	switch (huong) {
	case HUONG_QUA_PHAI:
		gioiHan = kg->getLeft();
		break;
	case HUONG_QUA_TRAI:
		gioiHan = kg->getRight();
		break;
	case HUONG_LEN_TREN:
		gioiHan = kg->getBottom();
		break;
	case HUONG_XUONG_DUOI:
		gioiHan = kg->getTop();
		break;
	case DICH_CHUYEN_TUC_THOI:
		gioiHan = kg->getTop();
		break;
	}

	camera->chuyenKhongGian(huong, gioiHan, loaiCong);
}

void QuanLyKhongGian::setChuyenXong(bool cx) {
	this->chuyenXong = cx;
}
void QuanLyKhongGian::setLoaiCong(int loaiCong) {
	this->loaiCong = loaiCong;
}
