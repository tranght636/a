#pragma once
#include "GameObject.h"

class VienDan1Len : public CGameObject
{
public:
	VienDan1Len();
	VienDan1Len(float vx, float vy);
	~VienDan1Len();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void filterCoObject(vector<LPGAMEOBJECT>* kq, vector<LPGAMEOBJECT>* coObjects);

};

