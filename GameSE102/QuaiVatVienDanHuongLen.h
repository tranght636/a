#pragma once
#include "QuaiVat.h"

class QuaiVatVienDanHuongLen : public QuaiVat
{
	/*bool onehit = true;
	int loai;
	float gioiHanTrai;
	float gioiHanPhai;
	bool move = false;*/
	float vxDiChuyen, vyDiChuyen;
	int diChuyen = 0;
	bool tanCong = false;
public:
	QuaiVatVienDanHuongLen();
	~QuaiVatVienDanHuongLen();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	//void setLoai(int loai) { this->loai = loai; }
	//void setGioiHanTrai(float gioiHanTrai) { this->gioiHanTrai = gioiHanTrai; }
	//void setGioiHanPhai(float gioiHanPhai) { this->gioiHanPhai = gioiHanPhai; }
	void setDiChuyen(int diChuyen) { this->diChuyen = diChuyen; }



	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects);
};




