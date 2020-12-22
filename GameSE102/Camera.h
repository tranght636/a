#pragma once
#include<d3dx9.h>
#include "GameConfig.h"

#define BINH_THUONG 1
#define CHUYEN_KHONG_GIAN 2

#define TOC_DO_CHUYEN 2.5f

#define MAP_WIDTH	2048
#define	MAP_HEIGHT 2048 

#define MAP_WIDTH_THUC_TE	2830
#define	MAP_HEIGHT_THUC_TE	2302 

class Camera
{
	float x;
	float y;
	float width;
	float height;
	int status;
	static Camera* instance;

	void xuLyBinhThuong();
	void xuLyChuyenKhongGian();

	// chuyển không gian
	int huong;
	int gioiHan;
	int loaiCong;

	float xHienTai;
	float yHienTai;
public:
	static Camera* getInstance();
	float getX();
	float getY();
	float getLeft();
	float getTop();
	float getRight();
	float getBottom();

	float getMidY(); 

	void reset();
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }

	int getStatus() { return this->status; }

	void update();

	void chuyenKhongGian(int huong, int gioiHan, int loaiCong);
	Camera();
	~Camera();

	void saveViTriHienTai(float x, float y) { this->xHienTai = x, this->yHienTai = y; }
	float getXHienTai() { return xHienTai; }
	float getYHienTai() { return yHienTai; }
	float getWidth() { return width; }
	float getHeight() { return height; }
};

