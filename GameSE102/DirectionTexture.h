#pragma once
#include "CWindow.h"

class DirectionTexture
{
	static DirectionTexture* instance;
public:
	static DirectionTexture* getInstance();
	void SetDirection(bool isDirRight, int x, int widthCurrent, int width);
	DirectionTexture();
	~DirectionTexture();
};

