#pragma once
#include "CPlayer.h"

#define STATUS_BINH_THUONG 1
#define STATUS_CHUYEN_KHONG_GIAN 2
#define STATUS_BAN 3
#define STATUS_CHET 4



#define PLAYER_XE_WALKING_SPEED 0.1f
#define PLAYER_XE_JUMP_SPEED_Y 0.26f
#define PLAYER_XE_GRAVITY 0.0005f

#define PLAYER_XE_ANI_DUNG_YEN 0
#define PLAYER_XE_ANI_CHAY 1
#define PLAYER_XE_ANI_QUAY_DAU	2
#define PLAYER_XE_ANI_NO	9

#define PLAYER_XE_NHAY_DUNG_YEN	3
#define PLAYER_XE_NHAY_DI_CHUYEN	4
#define PLAYER_XE_BAN_45_DUNG_YEN	5
#define PLAYER_XE_BAN_90_DUNG_YEN	6
#define PLAYER_XE_BAN_90_DI_CHUYEN	7
#define PLAYER_XE_CHUYEN_PLAYER	8
#define PLAYER_XE_TIME_QUAY_DAU	100

#define STATUS_BAN_NGANG	1
#define STATUS_BAN_LEN	2

#define TIME_DANG_CHET 3000

class PlayerXe : public CPlayer
{
	static PlayerXe* instance;
	bool isNhay;
	bool isDuocNhayCao = true;
	bool isStartQuayDau = false;
	int statusBan;
	bool is90 = false;
	bool isDangChet = false;
	int alpha = 255;
public:
	PlayerXe();
	~PlayerXe();
	static PlayerXe * getInstance();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL) override;
	void Render() override;
	void setNhay(bool isOnGround) { this->isNhay = isOnGround; }
	bool getNhay() { return this->isNhay; }

	void xuLyTrangThaiBinhThuong(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void xyLyChuyenKhongGian();
	//void xuLyBan();
	void xuLyBan(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void xuLyChet() override;
	void filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects);

};

