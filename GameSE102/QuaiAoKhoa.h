#pragma once
#include "QuaiVat.h"

class QuaiAoKhoa : public QuaiVat
{
	float x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, xBD, yBD;
	int diChuyen = 0;
public:
	QuaiAoKhoa();
	~QuaiAoKhoa();
	void setX1(float x1) { this->x1 = x1; }
	void setX2(float x2) { this->x2 = x2; }
	void setX3(float x3) { this->x3 = x3; }
	void setX4(float x4) { this->x4 = x4; }
	void setX5(float x5) { this->x5 = x5; }
	float getX1() { return this->x1; }
	float getX2() { return this->x2; }
	float getX3() { return this->x3; }
	float getX4() { return this->x4; }
	float getX5() { return this->x5; }
	void setY1(float y1) { this->y1 = y1; }
	void setY2(float y2) { this->y2 = y2; }
	void setY3(float y3) { this->y3 = y3; }
	void setY4(float y4) { this->y4 = y4; }
	void setY5(float y5) { this->y5 = y5; }
	float getY1() { return this->y1; }
	float getY2() { return this->y2; }
	float getY3() { return this->y3; }
	float getY4() { return this->y4; }
	float getY5() { return this->y5; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;


};





