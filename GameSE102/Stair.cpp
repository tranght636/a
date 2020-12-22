#include "Stair.h"
#include "CPlayer.h"
#include "CSampleKeyHandler.h"

Stair::Stair(float x, float y, float width, float height, int isTop, int isRightStair) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->isTop = isTop;
	this->isRightStair = isRightStair;
}

void Stair::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CPlayer* player = CPlayer::getInstane();
	float xPlayerOnStair, yPlayerOnStair;
	if (Collision::checkAABB(this, CPlayer::getInstane())) {
		if (this->isTop) {
			player->setIsGiaoStair(true);
		}
		//if (CPlayer::getInstane()->getPrepareGoStair() == PLAYER_PREPARE_STAIR_UP) {
		if (CSampleKeyHandler::isUpDown 
			&& !this->isTop
			&& player->getOnGround()
			&& player->getStateCommon() != PLAYER_STATE_ON_STAIR) {
				player->setIsEndStair(false);	
				player->setStateCommon(PLAYER_STATE_ON_STAIR);
				player->setStateOnStair(PLAYER_STATE_STAND_STAIR);
				if (this->isRightStair) {
					xPlayerOnStair = this->getMidX() - this->getWidth();
					yPlayerOnStair = this->getBottom() - player->getHeight();
				}
				else {
					xPlayerOnStair = this->getMidX()+2;
					yPlayerOnStair = this->getBottom() - player->getHeight();
				}
				player->SetPosition(xPlayerOnStair, yPlayerOnStair);
				player->setStairDirection(this->isRightStair ? 1 : -1);
				player->setDirection(this->isRightStair ? 1 : -1);
				player->setAni(PLAYER_ANI_STAND_STAIR_UP);
			//player->SetState(PLAYER_STATE_ON_STAIR);
		}
		else if (CSampleKeyHandler::isDownDown
			&& this->isTop
			&& player->getOnGround()
			&& player->getStateCommon() != PLAYER_STATE_ON_STAIR) {
				player->setIsEndStair(false);
				player->setStateCommon(PLAYER_STATE_ON_STAIR);
				player->setStateOnStair(PLAYER_STATE_STAND_STAIR);
				if (this->isRightStair) {
					xPlayerOnStair = this->getX() - player->getWidth();
					yPlayerOnStair = this->getBottom() + this->getHeight() / 2 - player->getHeight();
				}
				else {
					xPlayerOnStair = this->getRight() + 2;
					yPlayerOnStair = this->getBottom() + this->getHeight() / 2 - player->getHeight();
				}
				player->SetPosition(xPlayerOnStair, yPlayerOnStair);
				player->setStairDirection(this->isRightStair ? 1 : -1);
				player->setDirection(this->isRightStair ? -1 : 1);
				player->setAni(PLAYER_ANI_STAND_STAIR_DOWN);
		}
		else if (player->getStateCommon() == PLAYER_STATE_ON_STAIR) {
			float vy = player->getVy();
			float vx = player->getVx();
			if ((vy < 0 && this->isTop && this->isRightStair && player->getRight() > this->getX() + 2)
				|| (vy < 0 && this->isTop && !this->isRightStair && player->getX() < this->getRight() - 2)) {
				//player->setDirection(this->isRightStair ? 1 : -1);
				if (vx > 0 && this->isRightStair || vx < 0 && !this->isRightStair)
					player->setIsEndStair(true);
			}
			if(vy > 0 && !this->isTop && this->getBottom() - 4 < player->getBottom()) {
				//player->setDirection(this->isRightStair ? -1 : 1);
				if(vx > 0 && !this->isRightStair || vx < 0 && this->isRightStair)
					player->setIsEndStair(true);
			}
		}
			
	}
}

Stair::Stair()
{
}


Stair::~Stair()
{
}
