
#pragma once
#include "QuaiVat.h"
#include "DanOfQuai.h"

#define ANI_DAN_OF_QUAI_VAT_DAU_SAU 100

class DanOfQuaiVatDauSau : public DanOfQuai
{
	
public:
	DanOfQuaiVatDauSau();
	~DanOfQuaiVatDauSau();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects);
	void setV();
};



