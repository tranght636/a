#include "Weapon.h"
#include "CPlayer.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects) {
}

void Weapon::Render() {
	
	CPlayer* player = CPlayer::getInstane();
	ani = 0;
	int direction = player->getDirection();
	if (player->GetState() == PLAYER_STATE_DUNG_DANH 
		|| player->GetState() == PLAYER_STATE_THANG_DANH) {
		int indexFrame = player->getCurrentFrame();
		if (!player->getIsLastAni()) {
			if (direction == 1) {
				if (indexFrame == 0) {
					x = player->getX() - 16;
					y = player->getY() + 6;
				}
				else if (indexFrame == 1) {
					x = player->getX() - 16;
					y = player->getY() + 3;
				}
				else if (indexFrame == 2) {
					x = player->getX() + 17;
					
					if (player->getAni() == PLAYER_ANI_LEN_THANG_DANH ) {
						y = player->getY() + 10;
					}
					else {
						y = player->getY() + 8;
					}

				}
			}
			else {
				if (indexFrame == 0) {
					x = player->getRight() + 7;
					y = player->getY() + 6;
				}
				else if (indexFrame == 1) {
					x = player->getRight() + 1;
					y = player->getY() + 2;
				}
				else if (indexFrame == 2) {
					x = player->getRight() - 17 - animation_set->at(ani)->getFrame(indexFrame)->GetSprite()->getWidth();
					if (player->getAni() == PLAYER_ANI_LEN_THANG_DANH) {
						y = player->getY() + 10;
					}
					else {
						y = player->getY() + 8;
					}

				}
			}
			
			animation_set->at(ani)->getFrame(indexFrame)->render(x, y, direction);
		}
		
		
	}
	else {
		x = y = -50;
	}
	//RenderBoundingBox(150);
}

void Weapon::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	CPlayer* player = CPlayer::getInstane();
	if ((player->GetState() == PLAYER_STATE_DUNG_DANH || player->GetState() == PLAYER_STATE_THANG_DANH)
		&& player->getCurrentFrame() == 2) {
		int ani = 0; // = player->levelWeapon()

		l = x;
		t = y;
		r = x + animation_set->at(ani)->getFrame(2)->GetSprite()->getWidth();
		b = y + animation_set->at(ani)->getFrame(2)->GetSprite()->getHeight();
	}
	
	
}
