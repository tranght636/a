#pragma once
#include "GameObject.h"
class VatPham : public CGameObject
{
	bool isTime = false;
public:
	VatPham();
	~VatPham();
	void setIsTime(bool isTime) { this->isTime = isTime; }
	bool getIsTime() { return this->isTime; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
};





