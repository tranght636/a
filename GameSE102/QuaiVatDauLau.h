#pragma once
#include "QuaiVat.h"

class QuaiVatDauLau : public QuaiVat
{
	bool isDuocDiChuyen = false;
	int soLanBan = 0;
	bool isChoPhepBan = true;
	bool isDiChuyenNguoc = false;
	float vLan2;
public:
	QuaiVatDauLau();
	~QuaiVatDauLau();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects);

};





