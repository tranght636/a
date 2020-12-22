#pragma once
#include "VatPham.h"

class ThanhMau
{
	float x, y;
	LPANIMATION_SET animation_set;
	int ani;
	
	static ThanhMau* instance;
public:
	static ThanhMau * getInstance();
	ThanhMau();
	~ThanhMau();
	void Update();
	void Render();
};









