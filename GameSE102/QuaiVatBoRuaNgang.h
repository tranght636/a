#pragma once
#include "QuaiVat.h"

class QuaiVatBoRuaNgang : public QuaiVat
{
public:
	QuaiVatBoRuaNgang();
	~QuaiVatBoRuaNgang();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects);

};





