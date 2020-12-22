#pragma once
#include "QuaiVat.h"

class QuaiVatBomz : public QuaiVat
{
public:
	QuaiVatBomz();
	~QuaiVatBomz();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
};





