#include "Duoc.h"
#include "CPlayer.h"
#include "PlayScence.h"
#include "RoiItem.h"


#define ITEM_ROI 1

Duoc::Duoc() : QuaiVat()
{

}


Duoc::~Duoc()
{
}

void Duoc::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects) {
	CPlayer* player = CPlayer::getInstane();
	if (Collision::checkAABB(this, player->getWeapon())) {
		createItem(x, y);
		this->release();
		return;
	}
}

void Duoc::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void Duoc::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 32;
}

void Duoc::createItem(float xItem, float yItem) {
	if (item != 0) {
		CGameObject* itemObj = NULL;
		switch (item)
		{
		case ITEM_ROI:
			itemObj = new RoiItem();
			LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(aniSetItem);
			itemObj->SetAnimationSet(ani_set);
			itemObj->SetPosition(xItem, yItem);
			break;
		}
		CPlayScene::objects.push_back(itemObj);
		
	}
}