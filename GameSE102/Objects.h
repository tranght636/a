#pragma once
#include "GameObject.h"

class Objects
{
	static Objects* instance;
	vector<LPGAMEOBJECT> objects;
public:
	static Objects* GetInstance();
	void addObject(LPGAMEOBJECT object);
	vector<LPGAMEOBJECT> getAllObjects();
	Objects();
	~Objects();
};

