#pragma once
#include "GameObject.h"

class CongKhongGian : public CGameObject
{
	int khongGianId;	// target scene to switch to 
	int huong;

	float xPlayer;
	float yPlayer;

	int loaiCong;
public:
	CongKhongGian();
	~CongKhongGian();

	CongKhongGian(float l, float t, float r, float b, int scene_id, int huong, float xPlayer, float yPlayer, int loaiCong);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	int getKhongGianId() { return khongGianId; }
	int getHuong() { return huong; }
	float getXPlayer() { return xPlayer; }
	float getYPlayer() { return yPlayer; }
	int getLoaiCong() { return loaiCong; }
};

