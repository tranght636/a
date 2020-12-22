#include "CongKhongGian.h"



CongKhongGian::CongKhongGian()
{
}


CongKhongGian::~CongKhongGian()
{
}


CongKhongGian::CongKhongGian(float l, float t, float w, float h, int khongGianId, int huong, float xPlayer, float yPlayer, int loaiCong)
{
	this->khongGianId = khongGianId;
	this->huong = huong;
	this->xPlayer = xPlayer;
	this->yPlayer = yPlayer;
	x = l;
	y = t;
	width = w;
	height = h;
	this->loaiCong = loaiCong;
}

void CongKhongGian::Render()
{
	//RenderBoundingBox(150);
}

void CongKhongGian::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}