#pragma once
#include "CKeyEventHandler.h"
#include "CPlayer.h"
#include "CWindow.h"



class CSampleKeyHandler : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	void xuLyPhimPlayerXe(int keyCode);
	void xuLyPhimPlayerNguoi(int keyCode);
	void xuLyPhimPlayerNguoi2(int keyCode);

public:
	static bool isXDown;
	static bool isXGiu;
	static bool isDownDown;
	static bool isUpDown;
	static bool isLeftDown;
	static bool isRightDown;
	static void update();
};