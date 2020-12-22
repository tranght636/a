#pragma once
#include "QuaiVat.h"
class ConCoc : public QuaiVat
{
public:
	ConCoc();
	~ConCoc();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
};