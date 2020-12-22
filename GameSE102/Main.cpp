#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "CWindow.h"
#include "Game.h"
#include "CSampleKeyHandler.h"
#include "GameConfig.h"



/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = CWindow::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = CWindow::GetInstance()->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = CWindow::GetInstance()->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		CGame::GetInstance()->GetCurrentScene()->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	} 

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			CWindow::GetInstance()->ProcessKeyboard();
			CGame::GetInstance()->GetCurrentScene()->Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}
	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CWindow::GetInstance()->CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	CWindow::GetInstance()->Init(hWnd);
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	CWindow::GetInstance()->InitKeyboard(new CSampleKeyHandler());
	//CGame::GetInstance()->Init();
	CGame::GetInstance()->Load(SENCE_CONFIG_PATH);

	Run();
	return 0;
}