#include "QuaiSungDauCong.h"
#include "PlayScence.h"
#include "DanOfQuaiSungDauCong.h"
#include "VienDan1Trai.h"
#include "VienDan1Len.h"


#define VAN_TOC_DAN 0.1
QuaiSungDauCong::QuaiSungDauCong() : QuaiVat()
{

}


QuaiSungDauCong::~QuaiSungDauCong()
{
}

void QuaiSungDauCong::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	Camera* cam = Camera::getInstance();
	if (this->x < cam->getX() || this->x > cam->getX() + cam->getWidth() ||
		this->y < cam->getY() || this->y > cam->getY() + cam->getHeight())
	{
		return;
	}
	if (this->timeDelay->delay(1000)) {
		float xDan = this->getMidX() + 10;
		float yDan = this->getMidY() - 4;
		DanOfQuaiSungDauCong* vienDan1 = new DanOfQuaiSungDauCong(VAN_TOC_DAN,0);
		vienDan1->setX(xDan);
		vienDan1->setY(yDan);
		DanOfQuaiSungDauCong* vienDan2 = new DanOfQuaiSungDauCong(-VAN_TOC_DAN,0);
		vienDan2->setX(xDan);
		vienDan2->setY(yDan);
		DanOfQuaiSungDauCong* vienDan3 = new DanOfQuaiSungDauCong(0, VAN_TOC_DAN);
		vienDan3->setX(xDan);
		vienDan3->setY(yDan);
		DanOfQuaiSungDauCong* vienDan4 = new DanOfQuaiSungDauCong(0,-VAN_TOC_DAN);
		vienDan4->setX(xDan);
		vienDan4->setY(yDan);
		CPlayScene::addObjectToGrid(vienDan1);
		CPlayScene::addObjectToGrid(vienDan2);
		CPlayScene::addObjectToGrid(vienDan3);
		CPlayScene::addObjectToGrid(vienDan4);

	}
	/*if (this->timeDelay->delay(1000)) {
		float xDan = this->getMidX() + 10;
		float yDan = this->getMidY() - 4;
		VienDan1Trai* vienDan1 = new VienDan1Trai(true,VAN_TOC_DAN, 0);
		vienDan1->setX(xDan);
		vienDan1->setY(yDan);
		VienDan1Trai* vienDan2 = new VienDan1Trai(false,-VAN_TOC_DAN, 0);
		vienDan2->setX(xDan);
		vienDan2->setY(yDan);
		VienDan1Len* vienDan3 = new VienDan1Len(0, VAN_TOC_DAN);
		vienDan3->setX(xDan);
		vienDan3->setY(yDan);
		VienDan1Len* vienDan4 = new VienDan1Len(0, -VAN_TOC_DAN);
		vienDan4->setX(xDan);
		vienDan4->setY(yDan);
		CPlayScene::addObjectToGrid(vienDan1);
		CPlayScene::addObjectToGrid(vienDan2);
		CPlayScene::addObjectToGrid(vienDan3);
		CPlayScene::addObjectToGrid(vienDan4);

	}*/
}

void QuaiSungDauCong::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void QuaiSungDauCong::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 25;
	bottom = y + 25;
}
