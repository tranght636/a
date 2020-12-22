#pragma once
#include "GameObject.h"

class Grid
{
	int x, y, w, h;
	
public:
	vector<LPGAMEOBJECT> objects;
	void setXYWH(int x, int y, int w, int h) { this->x = x, this->y = y, this->w = w, this->h = h; }
	Grid() {}
	void removeObject(LPGAMEOBJECT object);
	void addObject(LPGAMEOBJECT object);

	int getRight() { return this->x + this->w; }
	int getBottom() { return this->y + this->h; }
	void thucThiDelete();
};

