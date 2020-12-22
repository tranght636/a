#pragma once
#include "QuaiVat.h"
#include "CangChanBoss.h"
#include "BanChanBoss.h"

class Boss : public QuaiVat
{
	CangChanBoss* cbsTrai1;
	CangChanBoss* cbsTrai2;
	CangChanBoss* cbsTrai3;
	CangChanBoss* cbsTrai4;
	BanChanBoss* bcbTrai;

	CangChanBoss* cbsPhai1;
	CangChanBoss* cbsPhai2;
	CangChanBoss* cbsPhai3;
	CangChanBoss* cbsPhai4;
	BanChanBoss* bcbPhai;

	bool isXThu = true;
	bool isYThu = true;

	bool isTrXThu = false;
	bool isTrYThu = false;

	int statusBcbPhai;
	int statusBcbTrai;
	bool isQuyDaoChanTrai1;

	static Boss* instance;

	int mau;
public:
	static Boss* getInstance();
	Boss();
	~Boss();
	Boss(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void UpdateThanhPhan(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void truMau();
	void xuLyKhiBossDie();
};
