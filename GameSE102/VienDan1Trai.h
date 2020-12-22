#pragma once
#include "GameObject.h"

#define ANI_VIEN_DAN_1_TRAI 3
#define Vx_VIEN_DAN 0.2f

class VienDan1Trai : public CGameObject
{
	
public:
	VienDan1Trai();
	~VienDan1Trai();

	VienDan1Trai(int huong);

	VienDan1Trai(int isDirRight, float vx, float vy);


	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects);

};

