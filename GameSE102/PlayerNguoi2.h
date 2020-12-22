#pragma once
#include "CPlayer.h"

#define PLAYER_NGUOI2_ANI_DUNG_YEN_TRAI_PHAI	0
#define PLAYER_NGUOI2_ANI_DI_CHUYEN_TRAI_PHAI	1
#define PLAYER_NGUOI2_ANI_DUNG_YEN_LEN			2
#define PLAYER_NGUOI2_ANI_DI_CHUYEN_LEN			3
#define PLAYER_NGUOI2_ANI_DUNG_YEN_XUONG		4
#define PLAYER_NGUOI2_ANI_DI_CHUYEN_XUONG		5


#define PLAYER_NGUOI2_STATUS_BINH_THUONG	1
#define STATUS_CHUYEN_KHONG_GIAN 2
#define STATUS_BAN 3

#define PLAYER_NGUOI_WALKING_SPEED 0.1f
#define PLAYER_NGUOI_JUMP_SPEED_Y 0.5f
#define PLAYER_NGUOI_GRAVITY 0.002f


class PlayerNguoi2 : public CPlayer
{
	static PlayerNguoi2* instance;
	bool isNhay;
	int isLastAni = 0;
	int statusBan;
	bool is90 = false;
	int huong;
public:
	PlayerNguoi2();
	~PlayerNguoi2();

	static PlayerNguoi2* getInstance();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;

	void xuLyBinhThuong(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void xyLyChuyenKhongGian();
	void xuLyBan();
	void xuLyChet() override;

};

