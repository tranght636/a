#include "ThanhMau.h"
#include "Camera.h"
#include "CPlayer.h"
#define ANI_VAT_PHAM_Fr 90

ThanhMau* ThanhMau::instance = NULL;

ThanhMau* ThanhMau::getInstance() {
	if (instance == NULL) {
		instance = new ThanhMau();
	}
	return instance;
}


ThanhMau::ThanhMau()
{
	ani = 0;
	this->animation_set = CAnimationSets::GetInstance()->Get(ANI_VAT_PHAM_Fr);
}


ThanhMau::~ThanhMau()
{
}

void ThanhMau::Update() {
	this->ani = CPlayer::getInstance()->getPlayerHienTai()->getMau();
}

void ThanhMau::Render() {
	this->x = Camera::getInstance()->getX() + 5;
	this->y = Camera::getInstance()->getY() + 150;

	animation_set->at(ani)->Render(x, y, true, 180);
}

