#pragma once
#include "GameObject.h"
#include "DirectionTexture.h"
#include "Brick.h"

//#define PLAYER_ANI_IDLE		0
//#define PLAYER_ANI_WALKING	1

#define STATUS_BINH_THUONG 1
#define STATUS_DOI_PLAYER 2

#define PLAYER_XE 1
#define PLAYER_NGUOI 2
#define PLAYER_NGUOI_2 3

#define MAU 8

class CPlayer : public CGameObject
{
	static CPlayer * instance;
	static int playerHienTai;

	float xHienTai;
	float yHienTai;

	int level;
protected:
	int directionStart;
	int mau;
public:
	static CPlayer * getInstance();
	static CPlayer* getPlayerHienTai();
	static void setPlayerHienTai(int player);
	static void chuyenPlayer();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL) override;
	void Render() override;
	virtual void xuLyChet();

	
	int getCurrentFrame();
	void setDirectionStart(int direction) { this->directionStart = direction; }
	int getDirectionStart() { return this->directionStart; }

	void saveViTriHienTai(float x, float y) { this->xHienTai = x, this->yHienTai = y; }
	
	CPlayer();
	~CPlayer();
	float getXHienTai() { return xHienTai; }
	float getYHienTai() { return yHienTai; }

	void themMau();
	void truMau();

	void setMau(int mau) { this->mau = mau; }
	int getMau() { return this->mau; }
};