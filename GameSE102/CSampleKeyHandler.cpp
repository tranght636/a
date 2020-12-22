#include "CSampleKeyHandler.h"
#include "debug.h"
#include "CPlayer.h"
#include "PlayerXe.h"
#include "PlayerNguoi.h"
#include "PlayerNguoi2.h"


bool CSampleKeyHandler::isDownDown = false;
bool CSampleKeyHandler::isUpDown = false;

bool CSampleKeyHandler::isLeftDown = false;
bool CSampleKeyHandler::isRightDown = false;

bool CSampleKeyHandler::isXDown = false;
bool CSampleKeyHandler::isXGiu = false;


void CSampleKeyHandler::update() {
	
	isDownDown = GetAsyncKeyState(VK_DOWN);
	isUpDown = GetAsyncKeyState(VK_UP);
	isLeftDown = GetAsyncKeyState(VK_LEFT);
	isRightDown = GetAsyncKeyState(VK_RIGHT);
}

void CSampleKeyHandler::OnKeyDown(int keyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", keyCode);	

	if (PlayerXe::getInstance()->getStatus() == STATUS_CHUYEN_KHONG_GIAN) {
		return;
	}

	if (keyCode == DIK_LSHIFT || keyCode == DIK_RSHIFT) {
		CPlayer::getInstance()->setStatus(STATUS_DOI_PLAYER);
		return;
	}

	if (CPlayer::getInstance()->getPlayerHienTai() == PlayerXe::getInstance()) {
		xuLyPhimPlayerXe(keyCode);
	}
	else if(CPlayer::getInstance()->getPlayerHienTai() == PlayerNguoi::getInstance()){
		xuLyPhimPlayerNguoi(keyCode);
	}
	else {
		xuLyPhimPlayerNguoi2(keyCode);
	}
}

void CSampleKeyHandler::xuLyPhimPlayerXe(int keyCode) {
	switch (keyCode)
	{
	case DIK_Z:
		PlayerXe::getInstance()->setStatus(STATUS_BAN);
		break;
	case DIK_X:
		isXDown = true;
		break;
	}
}

void CSampleKeyHandler::xuLyPhimPlayerNguoi(int keyCode) {
	switch (keyCode)
	{
	case DIK_Z:
		PlayerNguoi::getInstance()->setStatus(STATUS_BAN);
		break;
	case DIK_X:
		isXDown = true;
		break;
	}
}
void CSampleKeyHandler::xuLyPhimPlayerNguoi2(int keyCode) {
	switch (keyCode)
	{
	case DIK_Z:
		PlayerNguoi2::getInstance()->setStatus(STATUS_BAN);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_X:
		break;
	}
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	
}
