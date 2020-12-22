#include "Thang.h"
#include "PlayerNguoi.h"
#include "Collision.h"
#include "CSampleKeyHandler.h"

Thang::Thang(float l, float t, float w, float h, bool isThangLen) {
	this->x = l;
	this->y = t;
	this->width = w;
	this->height = h;
	this->isThangLen = isThangLen;
}

void Thang::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	PlayerNguoi* player = PlayerNguoi::getInstance();

	// nếu thang giao với người
	if (!Collision::checkAABB(this, player)) {
		return;
	}

	CSampleKeyHandler::update();

	if (player->getStatus() == PLAYER_NGUOI_STATUS_BINH_THUONG) {
		// kiểm tra đi lên
		if (this->isThangLen && CSampleKeyHandler::isUpDown) {
			player->setX(this->x);
			player->setY(this->y - 10);
			player->setStatus(PLAYER_NGUOI_STATUS_DI_THANG);
		}
		// kiểm tra đi xuống
		else if(!this->isThangLen && CSampleKeyHandler::isDownDown){
			player->setX(this->x + this->width / 2 - 4);
			player->setY(this->y + 2);
			player->setStatus(PLAYER_NGUOI_STATUS_DI_THANG);
		}
		
		return;
	} 
	
	// kiểm tra dừng khi đi thang xuống
	if (player->getVy() > 0 && Collision::checkAABB(player, this) && this->isThangLen) {
		player->setStatus(PLAYER_NGUOI_STATUS_BINH_THUONG);
	}

	// kiểm tra dừng khi đi thang lên
	if (player->getVy() <= 0 && Collision::checkAABB(player, this) && !this->isThangLen) {
		if (CSampleKeyHandler::isLeftDown) {
			player->setX(player->getX() - 0.12f);
			player->setY(player->getY() - 0.5f);
			player->setStatus(PLAYER_NGUOI_STATUS_BINH_THUONG);
		}
		else if(CSampleKeyHandler::isRightDown){
			player->setX(player->getX() + 1.0f);
			player->setY(player->getY() - 0.5f);
			player->setStatus(PLAYER_NGUOI_STATUS_BINH_THUONG);
		}
		
	}

} 

void Thang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}