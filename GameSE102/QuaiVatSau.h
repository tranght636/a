#pragma once
#include "QuaiVat.h"

class QuaiVatSau : public QuaiVat
{
	int loai;
	float gioiHanTrai;
	float gioiHanPhai;
public:
	QuaiVatSau();
	~QuaiVatSau();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void setLoai(int loai) { this->loai = loai; }
	void setGioiHanTrai(float gioiHanTrai) { this->gioiHanTrai = gioiHanTrai; }
	void setGioiHanPhai(float gioiHanPhai) { this->gioiHanPhai = gioiHanPhai; }
	void filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects);

};





