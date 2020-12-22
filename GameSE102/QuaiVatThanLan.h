#pragma once
#include "QuaiVat.h"

class QuaiVatThanLan : public QuaiVat
{
	bool isTanCong = false;
	bool isChamDat = false;
public:
	QuaiVatThanLan();
	~QuaiVatThanLan();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects);
};




