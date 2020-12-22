#pragma once
#include <unordered_map>
#include "KhongGian.h"

using namespace std;

#define LOAD_MAP 0
#define HUONG_QUA_PHAI	1
#define HUONG_QUA_TRAI	2
#define HUONG_LEN_TREN	3
#define HUONG_XUONG_DUOI	4
#define DICH_CHUYEN_TUC_THOI 5

class QuanLyKhongGian
{
private:
	static QuanLyKhongGian* instance;
	int khongGianHienTai;
	bool chuyenXong;
	int loaiCong;
	unordered_map<int, KhongGian*> dsKhongGian;
public:
	static QuanLyKhongGian* getInstance();
	QuanLyKhongGian();
	~QuanLyKhongGian();

	void chuyenKhongGian(int id, int huong, int loaiCong);
	void addKhongGian(KhongGian* kg);
	KhongGian* getKhongGian(int id);
	KhongGian* getKhongGianHienTai();
	void setChuyenXong(bool cx);
	bool getChuyenXong() { return chuyenXong; }
	void setLoaiCong(int loaiCong);
	int getLoaiCong() { return loaiCong; }
	void setKhongGianHienTaiId(int kg) { this->khongGianHienTai = kg; }
	int getKhongGianHienTaiId() { return this->khongGianHienTai; }

};

