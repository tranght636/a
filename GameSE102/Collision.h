#pragma once
#include "GameObject.h"

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

class Collision
{
public:
	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float &t,
		float &nx,
		float &ny);
	static bool checkAABB(LPGAMEOBJECT object1, LPGAMEOBJECT object2);
	Collision();
	~Collision();
};

