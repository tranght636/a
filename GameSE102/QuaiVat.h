#pragma once
#include "GameObject.h"
class QuaiVat : public CGameObject
{
protected:
	int item =0;	// phần thưởng khi đánh quái vật (nếu có); item = 0 => không có; 1: P,2:Fr,3:HNho,4:SamSet, 5:H
	int aniSetItem;

	
public:
	QuaiVat();
	~QuaiVat();
	int getItem() { return this->item; }
	void setItem(int item) { this->item = item; }
	int getAniSetItem() { return this->aniSetItem; }
	void setAniSetItem(int aniSetItem) { this->aniSetItem = aniSetItem; }
	void NewItem();
};

