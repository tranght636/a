#include "CPLayer.h"
#include "Portal.h"
#include "CSampleKeyHandler.h"
#include "QuaiVat.h"
#include "QuanLyKhongGian.h"
#include "CongKhongGian.h"

#include "PlayerXe.h"
#include "PlayerNguoi.h"
#include "PlayerNguoi2.h"


CPlayer* CPlayer::instance = NULL;
CPlayer* CPlayer::getInstance() {
	if (instance == NULL) {
		instance = new CPlayer();
	}
	return instance;
}

int CPlayer::playerHienTai = PLAYER_XE;
//int CPlayer::playerHienTai = PLAYER_NGUOI_2;
CPlayer* CPlayer::getPlayerHienTai() {
	if (playerHienTai == PLAYER_XE) {
		return PlayerXe::getInstance();
	}
	else if(playerHienTai == PLAYER_NGUOI){
		return PlayerNguoi::getInstance();
	}
	else {
		return PlayerNguoi2::getInstance();
	}
}

void CPlayer::setPlayerHienTai(int player) {
	playerHienTai = player;
}


void CPlayer::chuyenPlayer() {
	playerHienTai = playerHienTai == PLAYER_XE ? PLAYER_NGUOI : PLAYER_XE;
}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// TO-DO: check phím đổi player
	// status được thay đổi ở class SampleKeyHandler
	switch (this->status)
	{
	case STATUS_BINH_THUONG:

		if (this->playerHienTai == PLAYER_XE) {
			PlayerXe::getInstance()->Update(dt, coObjects);
		}
		else if(this->playerHienTai == PLAYER_NGUOI){
			PlayerNguoi::getInstance()->Update(dt, coObjects);
		}
		else {
			PlayerNguoi2::getInstance()->Update(dt, coObjects);
		}

		break;
	case STATUS_DOI_PLAYER: {
		// TO-DO: hientai = xe => xuất hiện người gần xe
		// hientai = nguoi => check người gần xe => đổi => giấu người đi
		PlayerNguoi* playerN = PlayerNguoi::getInstance();
		PlayerXe* playerX = PlayerXe::getInstance();
		PlayerNguoi2* playerN2 = PlayerNguoi2::getInstance();

		if (this->playerHienTai == PLAYER_XE) {
			// nếu xe đang nhảy hoặc đang di chuyển thì không cho đổi player
			if (playerX->getNhay() && playerX->getVx() == 0) {
				playerN->setX(playerX->getMidX() - playerN->getWidth() / 2);
				playerN->setY(playerX->getY());
				playerN->setVy(-0.2f);
				
				playerX->setAni(PLAYER_XE_CHUYEN_PLAYER);
				this->chuyenPlayer();
				
			}
		}
		else if(this->playerHienTai == PLAYER_NGUOI){
			
			bool isNguoiGanXe = Collision::checkAABB(playerX, playerN);
			if (isNguoiGanXe) {
				this->chuyenPlayer();
			}
			
		}
		//else {
		//	// chuyển người 1 qua người 2 vào map mới
		//	playerN2->setX(playerX->getX());
		//	playerN2->setY(playerX->getY());
		//}

		this->status = STATUS_BINH_THUONG;
		break;
	}
		
	default:
		break;
	}
	
}

void CPlayer::Render()
{
	/*PlayerNguoi2::getInstance()->Render();
	PlayerNguoi2::getInstance()->setX(1073);
	PlayerNguoi2::getInstance()->setY(1164);

	return;*/

	if (this->playerHienTai == PLAYER_NGUOI_2) {
		PlayerNguoi2::getInstance()->Render();
	}
	else {
		// Xe luôn được render, vì khi đổi player sang người
		// xe vẫn còn nằm đó
		PlayerXe::getInstance()->Render();
		if (this->playerHienTai == PLAYER_NGUOI) {
			PlayerNguoi::getInstance()->Render();
		}
	}
	
}

int CPlayer::getCurrentFrame() {
	return this->animation_set->at(ani)->getCurrentFrameIndex();
}

void CPlayer::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y + 2;
	right = x + getWidth();	// getAnimation(animationIndex)->getFrame(frameIndex)->getWidth();
	bottom = y + this->getHeight(); // ||||||||
}

void CPlayer::themMau() {
	if (this->mau == MAU) {
		return;
	}

	mau++;
}

void CPlayer::truMau() {
	mau--;
	DebugOut(L"[INFO] MAU: %d\n", mau);

	if (this->mau <= 0) {
		this->xuLyChet();
	}
}



CPlayer::CPlayer() {
	this->status = STATUS_BINH_THUONG;
	//this->playerHienTai = PLAYER_NGUOI_2;
}

CPlayer::~CPlayer() {

}

void CPlayer::xuLyChet() {

}
