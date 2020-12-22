#include <iostream>
#include <fstream>
#include <algorithm>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "CLayer.h"
#include "PlayerXe.h"
#include "PlayerNguoi.h"
#include "PlayerNguoi2.h"
#include "CSampleKeyHandler.h"
#include "QuanLyKhongGian.h"
#include "CongKhongGian.h"
#include "VienDan1Trai.h"
#include "VienDan1Len.h"
#include "Thang.h"

#include "QuaiVatDauSau.h"
#include "QuaiVatVienDanHuongLen.h"
#include "QuaiVatThanLan.h"
#include "QuaiVatRuoi.h"
#include "QuaiVatBoRua.h"
#include "QuaiVatSau.h"
#include "QuaiVatDauLau.h"
#include "QuaiVatBoRuaNgang.h"
#include "QuaiAoKhoa.h"
#include "QuaiMotMat.h"
#include "QuaiSungDauCong.h"
#include "QuaiVatBomz.h"

#include "Boss.h"
#include "CangChanBoss.h"
#include "BanChanBoss.h"

#include "Grid.h"
#include "QuanLyGrid.h"

#include "DanOfQuaiVatDauSau.h"
#include "DanOfQuaiVatDauLau.h"
#include "DanOfQuaiSungDauCong.h"

#include "VatPhamFr.h"
#include "VatPhamH.h"
#include "VatPhamHNho.h"
#include "VatPhamP.h"
#include "VatPhamSamSet.h"

#include "ThanhMau.h"
#include "VienDanPlayerNguoi2.h"



using namespace std;

vector<LPGAMEOBJECT> CPlayScene::objects;
vector<LPGAMEOBJECT> CPlayScene::listObject;


void CPlayScene::removeObject(LPGAMEOBJECT gameObject) {
	/*for (int i = 0; i < gameObject->dsGrid.size(); i++) {
		DongCotGrid dc = gameObject->dsGrid.at(i);
		Grid* grid = QuanLyGrid::getInstance()->getGrid(dc.d, dc.c);
		grid->removeObject(gameObject);
	}
	if (listObject.size() > 0) {
		listObject.erase(remove(listObject.begin(), listObject.end(), gameObject), listObject.end());
	}*/
}

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	//key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/
//
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TILEMAP	1
#define SCENE_SECTION_CAMRA		2
#define SCENE_SECTION_OBJECTS	3
#define SCENE_SECTION_KHONG_GIAN 4

#define OBJECT_TYPE_PLAYER_XE		0
#define OBJECT_TYPE_PLAYER_NGUOI	1
#define OBJECT_TYPE_PLAYER_NGUOI_2	4

#define OBJECT_TYPE_PORTAL				-1
#define OBJECT_TYPE_BRICK				-2
#define OBJECT_TYPE_CONG_KHONG_GIAN		-3
#define OBJECT_TYPE_THANG				-4

#define OBJECT_TYPE_VIEN_DAN1_TRAI			2
#define OBJECT_TYPE_VIEN_DAN1_LEN			3
#define OBJECT_TYPE_VIEN_DAN_PHAYER_NGUOI_2	5

#define OBJECT_TYPE_QUAI_VAT_DAU_SAU	10
#define OBJECT_TYPE_QUAI_VAT_VIENDAN_LEN	11
#define OBJECT_TYPE_QUAI_VAT_THAN_LAN	12
#define OBJECT_TYPE_QUAI_VAT_RUOI	13
#define OBJECT_TYPE_QUAI_VAT_BO_RUA	14
#define OBJECT_TYPE_QUAI_VAT_SAU	15
#define OBJECT_TYPE_QUAI_VAT_DAU_LAU	16
#define OBJECT_TYPE_QUAI_VAT_BO_RUA_NGANG	17
#define OBJECT_TYPE_QUAI_VAT_BOMZ	18

#define OBJECT_TYPE_QUAI_VAT_AO_KHOAC	51
#define OBJECT_TYPE_QUAI_VAT_MOT_MAT	53
#define OBJECT_TYPE_QUAI_VAT_SUNG_DAU_CONG	52


#define OBJECT_TYPE_QUAI_VAT_BOSS	600
//#define OBJECT_TYPE_QUAI_VAT_CANG_CHAN_BOSS	601
//#define OBJECT_TYPE_QUAI_VAT_BAN_CHAN_BOSS	602


#define OBJECT_TYPE_DAN_OF_QUAI_VAT_DAU_SAU	100
#define OBJECT_TYPE_DAN_OF_QUAI_VAT_DAU_LAU	101
#define OBJECT_TYPE_DAN_OF_QUAI_VAT_SUNG_DAU_CONG	102

#define OBJECT_TYPE_VAT_PHAM_P	70
#define OBJECT_TYPE_VAT_PHAM_FR	71
#define OBJECT_TYPE_VAT_PHAM_HNHO	72
#define OBJECT_TYPE_VAT_PHAM_SAM_SET 73
#define OBJECT_TYPE_VAT_PHAM_H	74

#define THANH_MAU 90


#define MAX_SCENE_LINE 100000

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	int tokenSize = tokens.size();
	if (tokenSize < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_BRICK: {
		float width, height;
		width = atof(tokens[3].c_str());
		height = atof(tokens[4].c_str());
		obj = new Brick(x, y, width, height);
		break;
	}
	case OBJECT_TYPE_CONG_KHONG_GIAN: {
		float w = atof(tokens[3].c_str());
		float h = atof(tokens[4].c_str());
		int khongGianId = atoi(tokens[5].c_str());
		int huong = atoi(tokens[6].c_str());
		float xPlayer = atoi(tokens[7].c_str());
		float yPlayer = atoi(tokens[8].c_str());
		int loaiCong = atoi(tokens[9].c_str());
		obj = new CongKhongGian(x, y, w, h, khongGianId, huong, xPlayer, yPlayer,loaiCong);
		break;
	}
	case OBJECT_TYPE_PORTAL: {
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		if (tokens.size() > 7) {
			float xPlayer = atof(tokens[7].c_str());
			float yPlayer = atof(tokens[8].c_str());
			float xCam = atof(tokens[9].c_str());
			float yCam = atof(tokens[10].c_str());
			int khongGianId = atof(tokens[11].c_str());
			((CPortal*)obj)->setViTriBatDau(xPlayer, yPlayer, xCam, yCam);
			((CPortal*)obj)->setKhongGian(khongGianId);
		}
		break;
	}
	case OBJECT_TYPE_THANG: {
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		bool isThangLen = atoi(tokens[6].c_str());
		
		obj = new Thang(x, y, w, h, isThangLen);
		break;
	}
	case OBJECT_TYPE_VIEN_DAN1_TRAI: {
		obj = new VienDan1Trai();
		break;
	}
	case OBJECT_TYPE_VIEN_DAN1_LEN: {
		obj = new VienDan1Len();
		break;
	}

	case OBJECT_TYPE_QUAI_VAT_DAU_SAU: {
		obj = new QuaiVatDauSau();
		if (tokens.size() > 4) {
			((QuaiVatDauSau*)obj)->setItem(atoi(tokens[4].c_str()));
		}
		break;
	}
	case OBJECT_TYPE_QUAI_VAT_VIENDAN_LEN: {
		obj = new QuaiVatVienDanHuongLen();
		if (tokens.size() >= 5) {
			float objAni = atoi(tokens[4].c_str());
			((QuaiVatVienDanHuongLen*)obj)->setAni(objAni);
			((QuaiVatVienDanHuongLen*)obj)->setVx(atoi(tokens[5].c_str()) * ((QuaiVatVienDanHuongLen*)obj)->getVx());
			((QuaiVatVienDanHuongLen*)obj)->setVy(atoi(tokens[6].c_str()) * ((QuaiVatVienDanHuongLen*)obj)->getVy());
			((QuaiVatVienDanHuongLen*)obj)->setItem(atoi(tokens[7].c_str()));

			//int loai = atoi(tokens[4].c_str());
			//float gioiHanTrai = atof(tokens[5].c_str());
			//float gioiHanPhai = atof(tokens[6].c_str());
			//((QuaiVatVienDanHuongLen*)obj)->setLoai(loai);
			//((QuaiVatVienDanHuongLen*)obj)->setGioiHanTrai(gioiHanTrai);
			//((QuaiVatVienDanHuongLen*)obj)->setGioiHanPhai(gioiHanPhai);
		}
		break;
	}
	case OBJECT_TYPE_QUAI_VAT_THAN_LAN: {
		obj = new QuaiVatThanLan();
		if (tokens.size() > 4) {
			((QuaiVatThanLan*)obj)->setItem(atoi(tokens[4].c_str()));
		}
		break;
	}
	case OBJECT_TYPE_QUAI_VAT_RUOI: {
		obj = new QuaiVatRuoi();
		if (tokens.size() > 4) {
			((QuaiVatRuoi*)obj)->setItem(atoi(tokens[4].c_str()));
		}
		break;
	}
	case OBJECT_TYPE_QUAI_VAT_BO_RUA: {
		obj = new QuaiVatBoRua();
		if (tokens.size() > 4) {
			((QuaiVatBoRua*)obj)->setItem(atoi(tokens[4].c_str()));
		}
		break;
	}
	case OBJECT_TYPE_QUAI_VAT_SAU: {
		obj = new QuaiVatSau();
		((QuaiVatSau*)obj)->setItem(atoi(tokens[4].c_str()));
		if (tokens.size() > 6) {
			((QuaiVatSau*)obj)->setItem(atoi(tokens[5].c_str()));
			int loai = atoi(tokens[6].c_str());
			float gioiHanTrai = atof(tokens[7].c_str());
			float gioiHanPhai = atof(tokens[8].c_str());
			//float 
			((QuaiVatSau*)obj)->setLoai(loai);
			((QuaiVatSau*)obj)->setGioiHanTrai(gioiHanTrai);
			((QuaiVatSau*)obj)->setGioiHanPhai(gioiHanPhai);
		}

		break;
	}
	case OBJECT_TYPE_QUAI_VAT_DAU_LAU: {
		obj = new QuaiVatDauLau();
		if (tokens.size() > 4) {
			((QuaiVatDauLau*)obj)->setItem(atoi(tokens[4].c_str()));
		}
		break;
	}
	case OBJECT_TYPE_QUAI_VAT_BO_RUA_NGANG: {
		obj = new QuaiVatBoRuaNgang();
		if (tokens.size() > 4) {
			((QuaiVatBoRuaNgang*)obj)->setItem(atoi(tokens[4].c_str()));
		}
		break;
	}
	case OBJECT_TYPE_DAN_OF_QUAI_VAT_DAU_SAU: {
		obj = new DanOfQuaiVatDauSau();
		break;
	}
	case OBJECT_TYPE_DAN_OF_QUAI_VAT_DAU_LAU: {
		obj = new DanOfQuaiVatDauLau();
		break;
	}
	case OBJECT_TYPE_QUAI_VAT_BOMZ:
		obj = new QuaiVatBomz();
		if (tokens.size() > 4) {
			((QuaiVatBomz*)obj)->setItem(atoi(tokens[4].c_str()));
		}
		break;
	case OBJECT_TYPE_QUAI_VAT_AO_KHOAC: {
		obj = new QuaiAoKhoa();
		if (tokens.size() > 4) {
			float x1 = atoi(tokens[4].c_str());
			float x2 = atoi(tokens[6].c_str());
			float x3 = atoi(tokens[8].c_str());
			float x4 = atoi(tokens[10].c_str());
			float x5 = atoi(tokens[12].c_str());
			float y1 = atoi(tokens[5].c_str());
			float y2 = atoi(tokens[7].c_str());
			float y3 = atoi(tokens[9].c_str());
			float y4 = atoi(tokens[11].c_str());
			float y5 = atoi(tokens[13].c_str());
			
			((QuaiAoKhoa*)obj)->setX1(x1);
			((QuaiAoKhoa*)obj)->setX2(x2);
			((QuaiAoKhoa*)obj)->setX3(x3);
			((QuaiAoKhoa*)obj)->setX4(x4);
			((QuaiAoKhoa*)obj)->setX5(x5);
			((QuaiAoKhoa*)obj)->setY1(y1);
			((QuaiAoKhoa*)obj)->setY2(y2);
			((QuaiAoKhoa*)obj)->setY3(y3);
			((QuaiAoKhoa*)obj)->setY4(y4);
			((QuaiAoKhoa*)obj)->setY5(y5);
			((QuaiAoKhoa*)obj)->setItem(atoi(tokens[14].c_str()));
		}
		break;
	}
	case OBJECT_TYPE_QUAI_VAT_MOT_MAT: {
		obj = new QuaiMotMat();
		if (tokens.size() > 4) {
			((QuaiMotMat*)obj)->setItem(atoi(tokens[4].c_str()));
		}
		break;
	}
	case OBJECT_TYPE_QUAI_VAT_SUNG_DAU_CONG: {
		obj = new QuaiSungDauCong();
		if (tokens.size() > 4) {
			((QuaiSungDauCong*)obj)->setItem(atoi(tokens[4].c_str()));
		}
		break;
	}
	case OBJECT_TYPE_VAT_PHAM_P: {
		obj = new VatPhamP();
		break;
	}
	
	case OBJECT_TYPE_VAT_PHAM_FR: {
		obj = new VatPhamFr();
		break;
	}
								
	case OBJECT_TYPE_VAT_PHAM_HNHO: {
		obj = new VatPhamHNho();
		break;
	}
							 
	case OBJECT_TYPE_VAT_PHAM_SAM_SET: {
		obj = new VatPhamSamSet();
		break;
	} 	
	case OBJECT_TYPE_VAT_PHAM_H: {
		obj = new VatPhamH();
		break;
	}
	case OBJECT_TYPE_QUAI_VAT_BOSS: {
		obj = new Boss(x, y);
		break;
	}			 
	/*case THANH_MAU: {
		obj = new ThanhMau();
		break;
	}*/

	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	obj->setStart(x, y);

	// if object < 0 -> object no have sprite and animation.
	if (object_type > 0) {
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
	}

	addObjectToGrid(obj);
	//objects.push_back(obj);
}

void CPlayScene::addObjectToGrid(LPGAMEOBJECT object) {
	vector<DongCotGrid> dongCotGrid = object->getDsGrid();

	for (int i = 0; i < dongCotGrid.size(); i++) {
		DongCotGrid dc = dongCotGrid.at(i);

		// lưu lại danh sach grid hiện tại
		object->dsGrid.push_back(dc);


		Grid* grid = QuanLyGrid::getInstance()->getGrid(dc.d, dc.c);

		grid->addObject(object);
	}
}


void CPlayScene::_ParseSection_TILEMAP(string line) {
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 2) return; // skip invalid lines - an object set must have at least id, x, y

	LPCWSTR pathImage = ToLPCWSTR(tokens[0]);
	LPCWSTR pathInfo = ToLPCWSTR(tokens[1]);
	TileMap::getInstance()->init(pathImage, pathInfo);
}

void CPlayScene::_ParseSection_CAMERA(string line) {
	if (line == "") return;
	int typeCam = atoi(line.c_str());
	if (typeCam) {
		int xCam = TileMap::getInstance()->getMapWidth() - SCREEN_WIDTH + 16;
		Camera::getInstance()->setX(xCam);
	}
	else {
		Camera::getInstance()->reset();
	}
}

void CPlayScene::parseSentionKhongGian(string line) {
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines - an object set must have at least id, x, y

	int id = atoi(tokens[0].c_str());
	float l = atof(tokens[1].c_str());
	float t = atof(tokens[2].c_str());
	float r = atof(tokens[3].c_str());
	float b = atof(tokens[4].c_str());

	KhongGian* kg = new KhongGian(id, l, t, r, b);
	QuanLyKhongGian::getInstance()->addKhongGian(kg);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; }
		if (line == "[TILEMAP]") { section = SCENE_SECTION_TILEMAP; continue; }
		if (line == "[CAMERA]") { section = SCENE_SECTION_CAMRA; continue; }
		if (line == "[KHONG_GIAN]") { section = SCENE_SECTION_KHONG_GIAN; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		switch (section) {
			case SCENE_SECTION_TILEMAP: _ParseSection_TILEMAP(line); break;
			//case SCENE_SECTION_CAMRA: _ParseSection_CAMERA(line); break;
			case SCENE_SECTION_KHONG_GIAN: parseSentionKhongGian(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);

}

void CPlayScene::Update(DWORD dt)
{
	QuanLyGrid::getInstance()->thucThiDelete();
	listObject.clear();
	listObject = QuanLyGrid::getInstance()->getObjectGiaoCamera();
	for (size_t i = 0; i < listObject.size(); i++)
	{
		if (listObject[i]->getIsDelete()) {
			continue;
		}

		listObject[i]->Update(dt, &listObject);
		listObject[i]->updateGrid();
		
	}

	CPlayer::getInstance()->Update(dt, &listObject);
	ThanhMau::getInstance()->Update();
	Camera::getInstance()->update();
}

void CPlayScene::Render()
{
	TileMap::getInstance()->render(Camera::getInstance());

	ThanhMau::getInstance()->Render();

	for (size_t i = 0; i < listObject.size(); i++)
	{
		if (listObject[i]->getIsDelete()) {
			continue;
		}

		listObject[i]->Render();
		//listObject[i]->RenderBoundingBox(150);
	}
		
	CPlayer::getInstance()->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	TileMap::getInstance()->clear();
	
	// clear listObject
	vector<vector<Grid*>> grids = QuanLyGrid::getInstance()->getGrids();
	for (int i = 0; i < grids.size(); i++) {
		for (int j = 0; j < grids.at(i).size(); j++) {
			vector<LPGAMEOBJECT> objects = grids.at(i).at(j)->objects;
			for (int idx = 0; idx < objects.size(); idx++) {
				objects.at(idx)->release();
			}
		}
		grids.at(i).clear();
	}

	grids.clear();

	QuanLyGrid::getInstance()->release();



	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}