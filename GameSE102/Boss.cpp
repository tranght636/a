#include <math.h>
#include "Boss.h"
#include "Brick.h"
#include "debug.h"
#include "Camera.h"
#include "QuanLyKhongGian.h"
#include "PlayerNguoi2.h"

#define X_CHAN_TRAI -9
#define Y_CHAN_TRAI 23
#define X_CHAN_PHAI 55
#define Y_CHAN_PHAI 23

#define SIZE_CANG_BOSS 16
#define KHOANG_CACH_TAM_CANG_BOSS 72
#define KHOANG_CACH_TAM_NGANG_CANG_BOSS 40

// ============ STATE CHAN PHAI ===========
#define STATE_1_XUONG 1
#define STATE_2_DUOI_PHAI 2
#define STATE_3_LEN_PHAI 3
#define STATE_4_XUONG_PHAI 4
#define STATE_5_DUOI_TRAI 5
#define STATE_6_LEN_TRAI 6
#define STATE_7_XUONG_TRAI 7
#define STATE_8_DUOI_PHAI 8
#define STATE_DOI 9
#define STATE_DOI_2 10

// ============ STATE CHAN PHAI ===========
#define STATE_TR_XUONG_1 1
#define STATE_2_TR_1_TRAI_DUOI_2 2
#define STATE_3_TR_2_TRAI_LEN_CHEO_3 3
#define STATE_4_TR_3_PHAI_LEN_4 4
#define STATE_5_TR_4_SANG_TRAI_5 5
#define STATE_6_TR_5_SANG_TRAI_6 6
#define STATE_7_TR_6_XUONG_TRAI_XEO_3 7
#define STATE_8_TR_3_XUONG_7 8
#define STATE_9_TR_7_SANG_TRAI_1 9
#define STATE_10_TR_1_TRAI_DUOI_2 10
#define STATE_11_TR_2_TRAI_LEN_8 11
#define STATE_12_TR_8_TRAI_LEN_XEO_4 12
#define STATE_13_TR_4_SANG_TRAI_6 13
#define STATE_14_TR_6_XUONG_8 14
#define STATE_15_TR_8_XUONG_XEO_7 15

#define STATE_TR_DOI -1
#define STATE_TR_DOI_2 -2

#define TIME_DOI	500
#define V_CHAN	0.05f

Boss::Boss() {

}

Boss::~Boss()
{

}

Boss* Boss::instance = NULL;

Boss* Boss::getInstance() {
	if (instance == NULL) {
		instance = new Boss(0, 0);
	}
	return instance;
}


Boss::Boss(float x, float y)
{
	this->x = x;
	this->y = y;

	this->cbsTrai1 = new CangChanBoss(X_CHAN_TRAI, Y_CHAN_TRAI);
	this->cbsTrai2 = new CangChanBoss(X_CHAN_TRAI, Y_CHAN_TRAI);
	this->cbsTrai3 = new CangChanBoss(X_CHAN_TRAI, Y_CHAN_TRAI);
	this->cbsTrai4 = new CangChanBoss(X_CHAN_TRAI, Y_CHAN_TRAI);
	this->bcbTrai = new BanChanBoss(X_CHAN_TRAI, Y_CHAN_TRAI);
	this->bcbTrai->setAni(1);

	this->cbsPhai1 = new CangChanBoss(X_CHAN_PHAI, Y_CHAN_PHAI);
	this->cbsPhai2 = new CangChanBoss(X_CHAN_PHAI, Y_CHAN_PHAI);
	this->cbsPhai3 = new CangChanBoss(X_CHAN_PHAI, Y_CHAN_PHAI);
	this->cbsPhai4 = new CangChanBoss(X_CHAN_PHAI, Y_CHAN_PHAI);
	this->bcbPhai = new BanChanBoss(X_CHAN_PHAI, Y_CHAN_PHAI);
	this->bcbPhai->setAni(0);
	this->bcbPhai->setVy(0.05);

	this->vx = 0.01f;
	this->vy = 0.01f;

	this->height = 65;
	this->width = 60;

	this->ani = 0;

	this->statusBcbPhai = STATE_1_XUONG;
	this->statusBcbTrai = STATE_TR_XUONG_1;
	this->isQuyDaoChanTrai1 = false;

	this->mau = 10;

	instance = this;
}
void Boss::UpdateThanhPhan(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {

	switch (this->statusBcbTrai)
	{
	case STATE_TR_XUONG_1:
		this->bcbTrai->setVx(0);
		this->bcbTrai->setVy(V_CHAN);

		this->isTrXThu = false;
		this->isTrYThu = false;

		if (this->bcbTrai->getYTuongDoi() - Y_CHAN_TRAI >= KHOANG_CACH_TAM_CANG_BOSS) {
			this->statusBcbTrai = STATE_2_TR_1_TRAI_DUOI_2;
		}

		break;
	case STATE_2_TR_1_TRAI_DUOI_2:
		this->bcbTrai->setVx(-V_CHAN);
		this->bcbTrai->setVy(0);

		this->isTrXThu = false;
		this->isTrYThu = false;

		if (X_CHAN_TRAI - this->bcbTrai->getXTuongDoi() >= KHOANG_CACH_TAM_NGANG_CANG_BOSS) {
			this->statusBcbTrai = STATE_3_TR_2_TRAI_LEN_CHEO_3;
		}
		break;

	case STATE_3_TR_2_TRAI_LEN_CHEO_3:
		this->bcbTrai->setVx(0.048f);
		this->bcbTrai->setVy(-V_CHAN);

		this->isTrXThu = this->bcbTrai->getXTuongDoi() < X_CHAN_TRAI;
		this->isTrYThu = true;

		if (this->bcbTrai->getXTuongDoi() - X_CHAN_TRAI >= 30) {
			this->statusBcbTrai = STATE_4_TR_3_PHAI_LEN_4;
		}

		break;
	case STATE_4_TR_3_PHAI_LEN_4:
		this->bcbTrai->setVx(0);
		this->bcbTrai->setVy(-V_CHAN);

		this->isTrXThu = false;
		this->isTrYThu = false;

		if (Y_CHAN_TRAI - this->bcbTrai->getYTuongDoi() >= KHOANG_CACH_TAM_CANG_BOSS) {
			this->statusBcbTrai = STATE_5_TR_4_SANG_TRAI_5;
		}

		break;
	case STATE_5_TR_4_SANG_TRAI_5:
		this->bcbTrai->setVx(-V_CHAN);
		this->bcbTrai->setVy(0);

		this->isTrXThu = true;
		this->isTrYThu = false;

		if (fabs(X_CHAN_TRAI - this->bcbTrai->getXTuongDoi()) < 1.0f) {
			this->statusBcbTrai = STATE_TR_DOI;
		}

		break;
	case STATE_TR_DOI:
		this->bcbTrai->setVx(0);
		this->bcbTrai->setVy(0);

		if (this->timeDelay->delay(TIME_DOI)) {
			this->statusBcbTrai = STATE_6_TR_5_SANG_TRAI_6;
		}

		break;
	case STATE_6_TR_5_SANG_TRAI_6:
		this->bcbTrai->setVx(-V_CHAN);
		this->bcbTrai->setVy(0);

		this->isTrXThu = false;
		this->isTrYThu = false;

		if (X_CHAN_TRAI - this->bcbTrai->getXTuongDoi() >= KHOANG_CACH_TAM_NGANG_CANG_BOSS) {
			this->statusBcbTrai = STATE_7_TR_6_XUONG_TRAI_XEO_3;
		}

		break;
	case STATE_7_TR_6_XUONG_TRAI_XEO_3:
		this->bcbTrai->setVx(0.048f);
		this->bcbTrai->setVy(V_CHAN);

		this->isTrXThu = this->bcbTrai->getXTuongDoi() < X_CHAN_TRAI;
		this->isTrYThu = true;

		if (this->bcbTrai->getXTuongDoi() - X_CHAN_TRAI >= 30) {
			this->statusBcbTrai = STATE_8_TR_3_XUONG_7;
		}

		break;
	case STATE_8_TR_3_XUONG_7:
		this->bcbTrai->setVx(0);
		this->bcbTrai->setVy(V_CHAN);

		this->isTrXThu = false;
		this->isTrYThu = false;

		if (this->bcbTrai->getYTuongDoi() - Y_CHAN_TRAI >= KHOANG_CACH_TAM_CANG_BOSS) {
			this->statusBcbTrai = STATE_9_TR_7_SANG_TRAI_1;
		}

		break;
	case STATE_9_TR_7_SANG_TRAI_1:
		this->bcbTrai->setVx(-V_CHAN);
		this->bcbTrai->setVy(0);

		this->isTrXThu = true;
		this->isTrYThu = false;

		if (X_CHAN_TRAI - this->bcbTrai->getXTuongDoi() >= 1.0f) {
			// set x chan trai
			this->bcbTrai->setXTuongDoi(X_CHAN_TRAI);
			this->cbsTrai1->setXTuongDoi(X_CHAN_TRAI);
			this->cbsTrai2->setXTuongDoi(X_CHAN_TRAI);
			this->cbsTrai3->setXTuongDoi(X_CHAN_TRAI);
			this->cbsTrai4->setXTuongDoi(X_CHAN_TRAI);
			this->statusBcbTrai = STATE_TR_DOI_2;

		}

		break;
	case STATE_TR_DOI_2:
		this->bcbTrai->setVx(0);
		this->bcbTrai->setVy(0);

		if (this->timeDelay->delay(TIME_DOI)) {
			this->statusBcbTrai = STATE_10_TR_1_TRAI_DUOI_2;
		}

		break;
	case STATE_10_TR_1_TRAI_DUOI_2:
		this->bcbTrai->setVx(-V_CHAN);
		this->bcbTrai->setVy(0);

		this->isTrXThu = false;
		this->isTrYThu = false;

		if (X_CHAN_TRAI - this->bcbTrai->getXTuongDoi() >= KHOANG_CACH_TAM_NGANG_CANG_BOSS) {
			this->statusBcbTrai = this->isQuyDaoChanTrai1 ? STATE_3_TR_2_TRAI_LEN_CHEO_3 : STATE_11_TR_2_TRAI_LEN_8;
			this->isQuyDaoChanTrai1 = !isQuyDaoChanTrai1;
		}

		break;
	case STATE_11_TR_2_TRAI_LEN_8:
		this->bcbTrai->setVx(0);
		this->bcbTrai->setVy(-V_CHAN);

		this->isTrXThu = false;
		this->isTrYThu = true;

		if (Y_CHAN_TRAI - this->bcbTrai->getYTuongDoi() >= 1.0f) {
			this->statusBcbTrai = STATE_12_TR_8_TRAI_LEN_XEO_4;
		}

		break;
	case STATE_12_TR_8_TRAI_LEN_XEO_4:
		this->bcbTrai->setVx(0.048f);
		this->bcbTrai->setVy(-V_CHAN);

		this->isTrXThu = false;
		this->isTrYThu = false;

		if (Y_CHAN_TRAI - this->bcbTrai->getYTuongDoi() >= KHOANG_CACH_TAM_CANG_BOSS) {
			this->statusBcbTrai = STATE_13_TR_4_SANG_TRAI_6;
		}

		break;
	case STATE_13_TR_4_SANG_TRAI_6:
		this->bcbTrai->setVx(-V_CHAN);
		this->bcbTrai->setVy(0);

		this->isTrXThu = this->bcbTrai->getXTuongDoi() > X_CHAN_TRAI;
		this->isTrYThu = false;

		if (X_CHAN_TRAI - this->bcbTrai->getXTuongDoi() >= KHOANG_CACH_TAM_NGANG_CANG_BOSS) {
			this->statusBcbTrai = STATE_14_TR_6_XUONG_8;
		}

		break;
	case STATE_14_TR_6_XUONG_8:
		this->bcbTrai->setVx(0);
		this->bcbTrai->setVy(V_CHAN);

		this->isTrXThu = false;
		this->isTrYThu = true;

		if (Y_CHAN_TRAI - this->bcbTrai->getYTuongDoi() <= 1.0f) {
			this->statusBcbTrai = STATE_15_TR_8_XUONG_XEO_7;
		}
		break;
	case STATE_15_TR_8_XUONG_XEO_7:
		this->bcbTrai->setVx(0.048f);
		this->bcbTrai->setVy(V_CHAN);

		this->isTrXThu = false;
		this->isTrYThu = false;

		if (this->bcbTrai->getXTuongDoi() - X_CHAN_TRAI >= 30) {
			this->statusBcbTrai = STATE_9_TR_7_SANG_TRAI_1;
		}
	default:
		break;
	}

	if (!this->isTrXThu) {
		float dxCbsTrai4BcbTrai = this->cbsTrai4->getXTuongDoi() - this->bcbTrai->getXTuongDoi();
		// nếu đi xuống, lấy y bcbPhai - y cbsPhai4
		if (this->bcbTrai->getVx() > 0) {
			dxCbsTrai4BcbTrai *= -1;
		}
		if (dxCbsTrai4BcbTrai > 10) {
			this->cbsTrai4->setVx(this->bcbTrai->getVx());
		}
		else {
			this->cbsTrai4->setVx(0);
		}


		float dxCbsTrai3CbsTrai4 = this->cbsTrai3->getXTuongDoi() - this->cbsTrai4->getXTuongDoi();
		if (this->cbsTrai4->getVx() > 0) {
			dxCbsTrai3CbsTrai4 *= -1;
		}
		if (dxCbsTrai3CbsTrai4 > 10) {
			this->cbsTrai3->setVx(this->cbsTrai4->getVx());
		}
		else {
			this->cbsTrai3->setVx(0);
		}


		float dxCbsTrai2CbsTrai3 = this->cbsTrai2->getXTuongDoi() - this->cbsTrai3->getXTuongDoi();
		if (this->cbsTrai3->getVx() > 0) {
			dxCbsTrai2CbsTrai3 *= -1;
		}
		if (dxCbsTrai2CbsTrai3 > 10) {
			this->cbsTrai2->setVx(this->cbsTrai3->getVx());
		}
		else {
			this->cbsTrai2->setVx(0);
		}


		float dxCbsTrai1CbsTrai2 = this->cbsTrai1->getXTuongDoi() - this->cbsTrai2->getXTuongDoi();
		if (this->cbsTrai2->getVx() > 0) {
			dxCbsTrai1CbsTrai2 *= -1;
		}
		if (dxCbsTrai1CbsTrai2 > 10) {
			this->cbsTrai1->setVx(this->cbsTrai2->getVx());
		}
		else {
			this->cbsTrai1->setVx(0);
		}
	}
	else {
		if (fabs(this->cbsTrai4->getXTuongDoi() - this->bcbTrai->getXTuongDoi()) < 1.0f) {
			this->cbsTrai4->setVx(this->bcbTrai->getVx());
		}
		else {
			this->cbsTrai4->setVx(0);
		}

		if (fabs(this->cbsTrai3->getXTuongDoi() - this->cbsTrai4->getXTuongDoi()) < 1.0f) {
			this->cbsTrai3->setVx(this->cbsTrai4->getVx());
		}
		else {
			this->cbsTrai3->setVx(0);
		}

		if (fabs(this->cbsTrai2->getXTuongDoi() - this->cbsTrai3->getXTuongDoi()) < 1.0f) {
			this->cbsTrai2->setVx(this->cbsTrai3->getVx());
		}
		else {
			this->cbsTrai2->setVx(0);
		}

		if (fabs(this->cbsTrai1->getXTuongDoi() - this->cbsTrai2->getXTuongDoi()) < 1.0f) {
			this->cbsTrai1->setVx(this->cbsTrai2->getVx());
		}
		else {
			this->cbsTrai1->setVx(0);
		}
	}

	// y giãn
	if (!this->isTrYThu) {
		float dxCbsTrai4BcbTrai = this->cbsTrai4->getYTuongDoi() - this->bcbTrai->getYTuongDoi();
		// nếu đi xuống, lấy y bcbTrai - y cbsTrai4
		if (this->bcbTrai->getVy() > 0) {
			dxCbsTrai4BcbTrai *= -1;
		}
		if (dxCbsTrai4BcbTrai > 15) {
			this->cbsTrai4->setVy(this->bcbTrai->getVy());
		}
		else {
			this->cbsTrai4->setVy(0);
		}


		float dxCbsTrai3CbsTrai4 = this->cbsTrai3->getYTuongDoi() - this->cbsTrai4->getYTuongDoi();
		if (this->cbsTrai4->getVy() > 0) {
			dxCbsTrai3CbsTrai4 *= -1;
		}
		if (dxCbsTrai3CbsTrai4 > 15) {
			this->cbsTrai3->setVy(this->cbsTrai4->getVy());
		}
		else {
			this->cbsTrai3->setVy(0);
		}


		float dxCbsTrai2CbsTrai3 = this->cbsTrai2->getYTuongDoi() - this->cbsTrai3->getYTuongDoi();
		if (this->cbsTrai3->getVy() > 0) {
			dxCbsTrai2CbsTrai3 *= -1;
		}
		if (dxCbsTrai2CbsTrai3 > 15) {
			this->cbsTrai2->setVy(this->cbsTrai3->getVy());
		}
		else {
			this->cbsTrai2->setVy(0);
		}


		float dxCbsTrai1CbsTrai2 = this->cbsTrai1->getYTuongDoi() - this->cbsTrai2->getYTuongDoi();
		if (this->cbsTrai2->getVy() > 0) {
			dxCbsTrai1CbsTrai2 *= -1;
		}
		if (dxCbsTrai1CbsTrai2 > 15) {
			this->cbsTrai1->setVy(this->cbsTrai2->getVy());
		}
		else {
			this->cbsTrai1->setVy(0);
		}
	}

	// y thu
	else {
		if (fabs(this->cbsTrai4->getYTuongDoi() - this->bcbTrai->getYTuongDoi()) < 1.0f) {
			this->cbsTrai4->setVy(this->bcbTrai->getVy());
		}
		else {
			this->cbsTrai3->setVy(0);
		}

		if (fabs(this->cbsTrai3->getYTuongDoi() - this->cbsTrai4->getYTuongDoi()) < 1.0f) {
			this->cbsTrai3->setVy(this->cbsTrai4->getVy());
		}
		else {
			this->cbsTrai3->setVy(0);
		}

		if (fabs(this->cbsTrai2->getYTuongDoi() - this->cbsTrai3->getYTuongDoi()) < 1.0f) {
			this->cbsTrai2->setVy(this->cbsTrai3->getVy());
		}
		else {
			this->cbsTrai2->setVy(0);
		}

		if (fabs(this->cbsTrai1->getYTuongDoi() - this->cbsTrai2->getYTuongDoi()) < 1.0f) {
			this->cbsTrai1->setVy(this->cbsTrai2->getVy());
		}
		else {
			this->cbsTrai1->setVy(0);
		}
	}


	this->bcbTrai->Update(dt, colliable_objects);
	this->cbsTrai1->Update(dt, colliable_objects);
	this->cbsTrai2->Update(dt, colliable_objects);
	this->cbsTrai3->Update(dt, colliable_objects);
	this->cbsTrai4->Update(dt, colliable_objects);




	// ====================Update chan phai ============================
	switch (this->statusBcbPhai)
	{
	case STATE_1_XUONG:
		this->bcbPhai->setVx(0);
		this->bcbPhai->setVy(V_CHAN);

		this->isXThu = false;
		this->isYThu = false;
		if (this->bcbPhai->getYTuongDoi() - Y_CHAN_PHAI >= KHOANG_CACH_TAM_CANG_BOSS) {
			this->statusBcbPhai = STATE_2_DUOI_PHAI;
		}

		break;
	case STATE_2_DUOI_PHAI:
		this->bcbPhai->setVx(V_CHAN);
		this->bcbPhai->setVy(0);

		this->isXThu = false;
		this->isYThu = false;

		if (this->bcbPhai->getXTuongDoi() - X_CHAN_PHAI >= KHOANG_CACH_TAM_NGANG_CANG_BOSS) {
			this->statusBcbPhai = STATE_3_LEN_PHAI;
		}

		break;
	case STATE_3_LEN_PHAI:
		this->bcbPhai->setVx(0);
		this->bcbPhai->setVy(-V_CHAN);

		this->isXThu = false;
		this->isYThu = false;

		if (Y_CHAN_PHAI - this->bcbPhai->getYTuongDoi() >= KHOANG_CACH_TAM_CANG_BOSS) {
			this->statusBcbPhai = STATE_4_XUONG_PHAI;
		}

		break;
	case STATE_4_XUONG_PHAI:
		this->bcbPhai->setVx(0);
		this->bcbPhai->setVy(V_CHAN);

		this->isXThu = false;
		this->isYThu = false;

		if (this->bcbPhai->getYTuongDoi() - Y_CHAN_PHAI >= KHOANG_CACH_TAM_CANG_BOSS) {
			this->statusBcbPhai = STATE_5_DUOI_TRAI;
		}
		break;
	case STATE_5_DUOI_TRAI:
		this->bcbPhai->setVx(-V_CHAN);
		this->bcbPhai->setVy(0);

		this->isXThu = true;
		this->isYThu = false;

		if (fabs(this->bcbPhai->getXTuongDoi() - X_CHAN_PHAI) < 1.0f) {
			this->bcbPhai->setXTuongDoi(X_CHAN_PHAI);
			this->cbsPhai1->setXTuongDoi(X_CHAN_PHAI);
			this->cbsPhai2->setXTuongDoi(X_CHAN_PHAI);
			this->cbsPhai3->setXTuongDoi(X_CHAN_PHAI);
			this->cbsPhai4->setXTuongDoi(X_CHAN_PHAI);

			this->statusBcbPhai = STATE_DOI;
		}
		break;
	case STATE_DOI:
		this->bcbPhai->setVx(0);
		this->bcbPhai->setVy(0);

		if (this->timeDelay->delay(TIME_DOI)) {
			this->statusBcbPhai = STATE_6_LEN_TRAI;
		}
		break;
	case STATE_6_LEN_TRAI:
		this->bcbPhai->setVx(-0.008);
		this->bcbPhai->setVy(-V_CHAN);

		this->isXThu = false;
		this->isYThu = false;

		if (Y_CHAN_PHAI - this->bcbPhai->getYTuongDoi() >= KHOANG_CACH_TAM_CANG_BOSS) {
			this->statusBcbPhai = STATE_7_XUONG_TRAI;
		}
		break;
	case STATE_7_XUONG_TRAI:
		this->bcbPhai->setVx(0);
		this->bcbPhai->setVy(V_CHAN);

		this->isXThu = false;
		this->isYThu = false;

		if (this->bcbPhai->getYTuongDoi() - Y_CHAN_PHAI >= KHOANG_CACH_TAM_CANG_BOSS) {
			this->statusBcbPhai = STATE_8_DUOI_PHAI;
		}
		break;
	case STATE_8_DUOI_PHAI:
		this->bcbPhai->setVx(V_CHAN);
		this->bcbPhai->setVy(0);

		this->isXThu = true;
		this->isYThu = false;

		if (fabs(this->bcbPhai->getXTuongDoi() - X_CHAN_PHAI) < 1.2f) {
			this->bcbPhai->setXTuongDoi(X_CHAN_PHAI);
			this->cbsPhai1->setXTuongDoi(X_CHAN_PHAI);
			this->cbsPhai2->setXTuongDoi(X_CHAN_PHAI);
			this->cbsPhai3->setXTuongDoi(X_CHAN_PHAI);
			this->cbsPhai4->setXTuongDoi(X_CHAN_PHAI);

			this->statusBcbPhai = STATE_DOI_2;
		}
		break;
	case STATE_DOI_2:
		this->bcbPhai->setVx(0);
		this->bcbPhai->setVy(0);

		if (this->timeDelay->delay(TIME_DOI)) {
			this->statusBcbPhai = STATE_2_DUOI_PHAI;
		}
		break;
	default:
		break;
	}


	if (!this->isXThu) {
		float dxCbsPhai4BcbPhai = this->cbsPhai4->getXTuongDoi() - this->bcbPhai->getXTuongDoi();
		// nếu đi xuống, lấy y bcbPhai - y cbsPhai4
		if (this->bcbPhai->getVx() > 0) {
			dxCbsPhai4BcbPhai *= -1;
		}
		if (dxCbsPhai4BcbPhai > 10) {
			this->cbsPhai4->setVx(this->bcbPhai->getVx());
		}
		else {
			this->cbsPhai4->setVx(0);
		}


		float dxCbsPhai3CbsPhai4 = this->cbsPhai3->getXTuongDoi() - this->cbsPhai4->getXTuongDoi();
		if (this->cbsPhai4->getVx() > 0) {
			dxCbsPhai3CbsPhai4 *= -1;
		}
		if (dxCbsPhai3CbsPhai4 > 10) {
			this->cbsPhai3->setVx(this->cbsPhai4->getVx());
		}
		else {
			this->cbsPhai3->setVx(0);
		}


		float dxCbsPhai2CbsPhai3 = this->cbsPhai2->getXTuongDoi() - this->cbsPhai3->getXTuongDoi();
		if (this->cbsPhai3->getVx() > 0) {
			dxCbsPhai2CbsPhai3 *= -1;
		}
		if (dxCbsPhai2CbsPhai3 > 10) {
			this->cbsPhai2->setVx(this->cbsPhai3->getVx());
		}
		else {
			this->cbsPhai2->setVx(0);
		}


		float dxCbsPhai1CbsPhai2 = this->cbsPhai1->getXTuongDoi() - this->cbsPhai2->getXTuongDoi();
		if (this->cbsPhai2->getVx() > 0) {
			dxCbsPhai1CbsPhai2 *= -1;
		}
		if (dxCbsPhai1CbsPhai2 > 10) {
			this->cbsPhai1->setVx(this->cbsPhai2->getVx());
		}
		else {
			this->cbsPhai1->setVx(0);
		}
	}
	else {
		if (fabs(this->cbsPhai4->getXTuongDoi() - this->bcbPhai->getXTuongDoi()) < 1.0f) {
			this->cbsPhai4->setVx(this->bcbPhai->getVx());
		}
		else {
			this->cbsPhai4->setVx(0);
		}

		if (fabs(this->cbsPhai3->getXTuongDoi() - this->cbsPhai4->getXTuongDoi()) < 1.0f) {
			this->cbsPhai3->setVx(this->cbsPhai4->getVx());
		}
		else {
			this->cbsPhai3->setVx(0);
		}

		if (fabs(this->cbsPhai2->getXTuongDoi() - this->cbsPhai3->getXTuongDoi()) < 1.0f) {
			this->cbsPhai2->setVx(this->cbsPhai3->getVx());
		}
		else {
			this->cbsPhai2->setVx(0);
		}

		if (fabs(this->cbsPhai1->getXTuongDoi() - this->cbsPhai2->getXTuongDoi()) < 1.0f) {
			this->cbsPhai1->setVx(this->cbsPhai2->getVx());
		}
		else {
			this->cbsPhai1->setVx(0);
		}
	}

	// y giãn
	if (!this->isYThu) {
		float dxCbsPhai4BcbPhai = this->cbsPhai4->getYTuongDoi() - this->bcbPhai->getYTuongDoi();
		// nếu đi xuống, lấy y bcbPhai - y cbsPhai4
		if (this->bcbPhai->getVy() > 0) {
			dxCbsPhai4BcbPhai *= -1;
		}
		if (dxCbsPhai4BcbPhai > 15) {
			this->cbsPhai4->setVy(this->bcbPhai->getVy());
		}
		else {
			this->cbsPhai4->setVy(0);
		}


		float dxCbsPhai3CbsPhai4 = this->cbsPhai3->getYTuongDoi() - this->cbsPhai4->getYTuongDoi();
		if (this->cbsPhai4->getVy() > 0) {
			dxCbsPhai3CbsPhai4 *= -1;
		}
		if (dxCbsPhai3CbsPhai4 > 15) {
			this->cbsPhai3->setVy(this->cbsPhai4->getVy());
		}
		else {
			this->cbsPhai3->setVy(0);
		}


		float dxCbsPhai2CbsPhai3 = this->cbsPhai2->getYTuongDoi() - this->cbsPhai3->getYTuongDoi();
		if (this->cbsPhai3->getVy() > 0) {
			dxCbsPhai2CbsPhai3 *= -1;
		}
		if (dxCbsPhai2CbsPhai3 > 15) {
			this->cbsPhai2->setVy(this->cbsPhai3->getVy());
		}
		else {
			this->cbsPhai2->setVy(0);
		}


		float dxCbsPhai1CbsPhai2 = this->cbsPhai1->getYTuongDoi() - this->cbsPhai2->getYTuongDoi();
		if (this->cbsPhai2->getVy() > 0) {
			dxCbsPhai1CbsPhai2 *= -1;
		}
		if (dxCbsPhai1CbsPhai2 > 15) {
			this->cbsPhai1->setVy(this->cbsPhai2->getVy());
		}
		else {
			this->cbsPhai1->setVy(0);
		}
	}

	// y thu
	else {
		if (fabs(this->cbsPhai4->getYTuongDoi() - this->bcbPhai->getYTuongDoi()) < 0.1f) {
			this->cbsPhai4->setVy(this->bcbPhai->getVy());
		}
		else {
			this->cbsPhai3->setVy(0);
		}

		if (fabs(this->cbsPhai3->getYTuongDoi() - this->cbsPhai4->getYTuongDoi()) < 0.1f) {
			this->cbsPhai3->setVy(this->cbsPhai4->getVy());
		}
		else {
			this->cbsPhai3->setVy(0);
		}

		if (fabs(this->cbsPhai2->getYTuongDoi() - this->cbsPhai3->getYTuongDoi()) < 0.1f) {
			this->cbsPhai2->setVy(this->cbsPhai3->getVy());
		}
		else {
			this->cbsPhai2->setVy(0);
		}

		if (fabs(this->cbsPhai1->getYTuongDoi() - this->cbsPhai2->getYTuongDoi()) < 0.1f) {
			this->cbsPhai1->setVy(this->cbsPhai2->getVy());
		}
		else {
			this->cbsPhai1->setVy(0);
		}
	}

	this->bcbPhai->Update(dt, colliable_objects);
	this->cbsPhai1->Update(dt, colliable_objects);
	this->cbsPhai2->Update(dt, colliable_objects);
	this->cbsPhai3->Update(dt, colliable_objects);
	this->cbsPhai4->Update(dt, colliable_objects);
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	if (this->x > 1945 || this->x < 1616) {
		this->vx *= -1;
	}
	if (this->y > 1012 || this->y < 820) {
		this->vy *= -1;
	}
	CGameObject::Update(dt);
	x += dx;
	y += dy;

	UpdateThanhPhan(dt, colliable_objects);

}

void Boss::Render() {
	animation_set->at(ani)->Render(x, y);

	this->cbsTrai1->Render();
	this->cbsTrai2->Render();
	this->cbsTrai3->Render();
	this->cbsTrai4->Render();
	this->bcbTrai->Render();

	this->cbsPhai1->Render();
	this->cbsPhai2->Render();
	this->cbsPhai3->Render();
	this->cbsPhai4->Render();
	this->bcbPhai->Render();
}

void Boss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 60;
	bottom = y + 65;
}

void Boss::truMau() {
	if (this->mau <= 0) {
		this->mau = 0;
		return;
	}

	this->mau--;

	if (mau == 0) {
		this->xuLyKhiBossDie();
	}
}

void Boss::xuLyKhiBossDie() {
	Camera::getInstance()->setX(1);
	Camera::getInstance()->setY(1808);

	QuanLyKhongGian::getInstance()->setKhongGianHienTaiId(2);

	PlayerNguoi2::getInstance()->SetPosition(149, 1895);
}

