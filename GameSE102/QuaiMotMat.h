#pragma once
#include "QuaiVat.h"

class QuaiMotMat : public QuaiVat
{
	bool isDungYen = true;
public:
	QuaiMotMat();
	~QuaiMotMat();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
};





