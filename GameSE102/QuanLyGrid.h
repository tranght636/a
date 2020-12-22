#pragma once
#include "GameObject.h"
#include "Grid.h"

class QuanLyGrid
{
	static QuanLyGrid* instance;
	vector<vector<Grid*>> grids;
	int soCot;
	int soDong;
	vector<LPGAMEOBJECT> objectToDelete;
public:
	static int widthGrid;
	static int heightGrid;
	static QuanLyGrid* getInstance();
	QuanLyGrid();
	Grid* getGrid(int d, int c);
	vector<LPGAMEOBJECT> getObjectGiaoCamera();
	void getObjectUpdate(vector<LPGAMEOBJECT>& listObject, Grid* grid);
	vector<vector<Grid*>> getGrids() { return this->grids; }
	void release();
	void thucThiDelete();
	void addObjectToDelete(LPGAMEOBJECT obj);
};

