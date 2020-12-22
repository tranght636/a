#pragma once
#include "GameObject.h"

#define ANI_VIEN_DAN_1_TRAI 0
#define Vx_VIEN_DAN 0.2f

class VienDanPlayerNguoi : public CGameObject
{

public:
	VienDanPlayerNguoi();
	~VienDanPlayerNguoi();
	VienDanPlayerNguoi(int huong);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects);

};

