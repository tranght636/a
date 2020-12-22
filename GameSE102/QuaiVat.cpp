#include "QuaiVat.h"
#include "CPlayer.h"
#include "QuanLyGrid.h"
#include "PlayScence.h"

#include "VatPhamFr.h"
#include "VatPhamH.h"
#include "VatPhamHNho.h"
#include "VatPhamP.h"
#include "VatPhamSamSet.h"


QuaiVat::QuaiVat()
{
}


QuaiVat::~QuaiVat()
{
}
void QuaiVat::NewItem() {
	if (this->item == 0) {
		return;
	}
	else {
		VatPham* obj = NULL;
		//item = 0 = > kh�ng c�; 1: P, 2 : Fr, 3 : HNho, 4 : SamSet, 5 : H
		switch (this->item)
		{
		case 1:
			obj = new VatPhamP();
			break;
		case 2:
			obj = new VatPhamFr();
			break;
		case 3:
			obj = new VatPhamHNho();
			break;
		case 4:
			obj = new VatPhamSamSet();
			break;
		case 5:
			obj = new VatPhamH();
			break;
		default:
			break;
		}
		obj->setIsTime(true);
		obj->setX(this->x);
		obj->setY(this->y);
		CPlayScene::addObjectToGrid(obj);
	}
}

//void QuaiVat::release() {
//	for (int i = 0; i < this->dsGrid.size(); i++) {
//		DongCotGrid dc = this->dsGrid.at(i);
//		Grid* grid = QuanLyGrid::getInstance()->getGrid(dc.d, dc.c);
//		grid->removeObject(this);
//	}
//
//	delete this;
//}
