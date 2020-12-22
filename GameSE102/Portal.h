#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id, khongGianId;	// target scene to switch to 
	float xPlayer, yPlayer, xCam, yCam;
public:
	CPortal(float l, float t, float r, float b, int scene_id);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	int GetSceneId() { return scene_id; }
	void setViTriBatDau(float xPlayer, float yPlayer, float xCam, float yCam) { this->xPlayer = xPlayer, this->yPlayer = yPlayer, this->xCam = xCam, this->yCam = yCam, this->khongGianId;}
	float getXPlayer() { return this->xPlayer; }
	float getYPlayer() { return this->yPlayer; }
	float getXCam() { return this->xCam; }
	float getYCam() { return this->yCam; }
	int getKhongGianId() { return khongGianId; }
	void setKhongGian(int kg) { this->khongGianId = kg; }

};