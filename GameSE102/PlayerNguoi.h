#pragma once
#include "CPlayer.h"

#define PLAYER_NGUOI_ANI_DUNG_YEN			0
#define PLAYER_NGUOI_ANI_DI_CHUYEN			1
#define PLAYER_NGUOI_ANI_LEO_THANG			2
#define PLAYER_NGUOI_ANI_CHET				3
#define PLAYER_NGUOI_ANI_LEO_THANG_DUNG		4
#define PLAYER_NGUOI_ANI_BO					5




#define PLAYER_NGUOI_STATUS_BINH_THUONG	1
#define PLAYER_NGUOI_STATUS_DI_THANG	2


#define PLAYER_NGUOI_WALKING_SPEED 0.1f
#define PLAYER_NGUOI_JUMP_SPEED_Y 0.5f
#define PLAYER_NGUOI_GRAVITY 0.002f

#define STATUS_BAN 3

class PlayerNguoi : public CPlayer
{
	static PlayerNguoi* instance;
	bool isNhay;
	bool hetThang;
	int khongGianIdHienTai;
	int huong;
public:
	PlayerNguoi();
	~PlayerNguoi();

	static PlayerNguoi * getInstance();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL) override;
	void Render() override;

	void setHetThang(bool hetThang) { this->hetThang = hetThang; }
	bool getHetThang() { return this->hetThang; }

	void xuLyBinhThuong(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void xuLyDiThang(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void setKgHienTai(int kg) { this->khongGianIdHienTai = kg; }
	int getKgHienTai() { return this->khongGianIdHienTai; }
	void xuLyBan();
	void xuLyChet() override;

};

