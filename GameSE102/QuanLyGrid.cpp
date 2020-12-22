#include "QuanLyGrid.h"
#include "GameConfig.h"
#include "Camera.h"
#include "TileMap.h"
#include "QuanLyKhongGian.h"

int QuanLyGrid::widthGrid = 0;
int QuanLyGrid::heightGrid = 0;

QuanLyGrid::QuanLyGrid() {
	TileMap* map = TileMap::getInstance();
	Camera* camera = Camera::getInstance();

	QuanLyGrid::widthGrid = (int)map->getMapWidth() / ceil(map->getMapWidth() / camera->getWidth());
	QuanLyGrid::heightGrid = ((int)map->getMapHeight()) / ceil((map->getMapHeight()) / camera->getHeight());

	// 9 dòng 10 côt.
	this->soCot = map->getMapWidth() / QuanLyGrid::widthGrid;
	this->soDong = map->getMapHeight() / QuanLyGrid::heightGrid;

	for (int d = 0; d < soDong; d++) {
		vector<Grid*> gridDong;
		for (int c = 0; c < soCot; c++) {
			Grid* grid = new Grid();
			int x = c * QuanLyGrid::widthGrid;
			int y = d * QuanLyGrid::heightGrid;
			grid->setXYWH(x, y, QuanLyGrid::widthGrid, QuanLyGrid::heightGrid);
			gridDong.push_back(grid);
		}
		this->grids.push_back(gridDong);
	}
}

QuanLyGrid* QuanLyGrid::instance = NULL;
QuanLyGrid* QuanLyGrid::getInstance() {
	if (instance == NULL) {
		instance = new QuanLyGrid();
	}
	return instance;
}

Grid* QuanLyGrid::getGrid(int d, int c) {
	if (d >= this->soDong) {
		d = this->soDong - 1;
	}
	if (c >= this->soCot) {
		c = this->soCot - 1;
	}
	return this->grids.at(d).at(c);
}

void getDongCotGrid(int x, int y, int& d, int& c) {
	c = x / QuanLyGrid::widthGrid;
	d = y / QuanLyGrid::heightGrid;
}

vector<LPGAMEOBJECT> QuanLyGrid::getObjectGiaoCamera() {
	vector<LPGAMEOBJECT> kq;
	kq.clear();

	Camera* camera = Camera::getInstance();

	// kiểm tra nếu đang chuyển không gian thì return kq;
	if (camera->getStatus() == CHUYEN_KHONG_GIAN) {
		return kq;
	}

	int xTraiTren = camera->getX();
	int yTraiTren = camera->getY();

	int dGrid1, cGrid1;
	getDongCotGrid(xTraiTren, yTraiTren, dGrid1, cGrid1);
	
	Grid* grid1 = this->getGrid(dGrid1, cGrid1);
	getObjectUpdate(kq, grid1);

	if (camera->getRight() > grid1->getRight()) {
		Grid* grid2 = this->getGrid(dGrid1, cGrid1 + 1);
		getObjectUpdate(kq, grid2);
	}

	if (camera->getBottom() > grid1->getBottom()) {
		Grid* grid3 = this->getGrid(dGrid1 + 1, cGrid1);
		getObjectUpdate(kq, grid3);
	}

	if (camera->getRight() > grid1->getRight() && camera->getBottom() > grid1->getBottom()) {
		Grid* grid4 = this->getGrid(dGrid1 + 1, cGrid1 + 1);
		getObjectUpdate(kq, grid4);
	}

	return kq;
}

void QuanLyGrid::getObjectUpdate(vector<LPGAMEOBJECT> &listObject, Grid* grid) {
	KhongGian* kg = QuanLyKhongGian::getInstance()->getKhongGianHienTai();

	for (int i = 0; i < grid->objects.size(); i++) {

		// checkobject thuộc khong gian
		float xObj = grid->objects.at(i)->getX();
		float yObj = grid->objects.at(i)->getY();
		if (!dynamic_cast<Brick*>(grid->objects.at(i)) &&
			(xObj < kg->getLeft() ||
			xObj > kg->getRight() ||
			yObj < kg->getTop() ||
			yObj > kg->getBottom())) {
			continue;
		}

		bool isChuaCo = true;

		for (int j = 0; j < listObject.size(); j++) {
			if (listObject.at(j) == grid->objects.at(i)) {
				isChuaCo = false;
				break;
			}
		}

		if (isChuaCo) {
			listObject.push_back(grid->objects.at(i));
		}	
	}
}

void QuanLyGrid::release() {
	delete instance;
	instance = NULL;
}

void QuanLyGrid::thucThiDelete() {
	//remove obj of vector
	for (int d = 0; d < this->soDong; d++) {
		for (int c = 0; c < this->soCot; c++) {
			this->grids.at(d).at(c)->thucThiDelete();
		}
	}

	for (int i = 0; i < this->objectToDelete.size(); i++) {
		delete this->objectToDelete.at(i);
	}

	this->objectToDelete.clear();
}

void QuanLyGrid::addObjectToDelete(LPGAMEOBJECT obj) {
	this->objectToDelete.push_back(obj);
}


