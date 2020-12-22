#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "CKeyEventHandler.h"
#include "Camera.h"

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024

#define WINDOW_CLASS_NAME L"GameSE104"
#define MAIN_WINDOW_TITLE L"GameSE104"

class CWindow
{
	static CWindow * __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

public:
	void InitKeyboard(LPKEYEVENTHANDLER handler);
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int achorX = 0, int achorY = 0, int alpha = 255);

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	static CWindow * GetInstance();
	HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight);
	LPDIRECT3DTEXTURE9 LoadTexture(LPCWSTR texturePath, D3DCOLOR transparentColor = 0);
	~CWindow();
};