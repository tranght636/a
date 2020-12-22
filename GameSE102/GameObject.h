#pragma once
#include <Windows.h>
#include <unordered_map>
#include "Sprites.h"
#include "Collision.h"
#include "Delay.h"
using namespace std;

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;
struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) {
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b) {
		return a->t < b->t;
	}
};

struct DongCotGrid
{
	int d, c;

};

class CGameObject
{
protected:
	float start_x;			// initial position of Player at scene
	float start_y;
	float x;
	float y;
	float width;
	float height;
	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt
	float vx;
	float vy;
	int nx;
	int status;
	bool isDirRight;
	bool isLastAni;
	DWORD dt;
	//static unordered_map<int, LPANIMATION> animations;

	int ani;
	LPANIMATION_SET animation_set;

	Delay* timeDelay = new Delay();

	bool isDelete = false;
	
public:
	//static void AddAnimation(int aniId);
	vector<DongCotGrid> dsGrid;
	void SetPosition(float x, float y) { this->x = x, this->y = y; }

	void setStart(float x, float y) { this->start_x = x, this->start_y = y; }
	void getStart(float &x, float &y) { x = this->start_x, y = this->start_y; }
	float getStartX() { return this->start_x; }
	float getStartY() { return this->start_y; }

	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void setSize(float x, float y, float width, float height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	float getX() { return this->x; }
	float getY() { return this->y; }
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }

	float getWidth() {
		/*if (ani != -1) {
			LPANIMATION animations = animation_set->at(ani);
			return animations->getCurrentFrame()->GetSprite()->getWidth();
		}
		else {
			return this->width;
		}*/
		return this->width;
	}
	float getHeight() { 
		if (ani != -1) {
			LPANIMATION animations = animation_set->at(ani);
			float height = animations->getCurrentFrame()->GetSprite()->getHeight();
			return height;
		}
		return this->height; 
	}

	// get độ chệnh lệnh rộng 2 frame
	float getDW() {
		if (ani != -1) {
			LPANIMATION animations = animation_set->at(ani);
			float currenWidth = animations->getCurrentFrame()->GetSprite()->getWidth();
			float nextWidth = 0;
			if (animations->getNextFrame() != 0) {
				nextWidth = animations->getNextFrame()->GetSprite()->getWidth();
			}
			
			return nextWidth - currenWidth;
		}
	}

	void setIsDelete(bool isDelete) { this->isDelete = isDelete; }
	bool getIsDelete() { return this->isDelete; }

	float getBottom() { return y + getHeight(); }
	float getRight() { return x + getWidth(); }
	float getMidX() { return x + getWidth() / 2; }
	float getMidY() { return y + getHeight() / 2; }
	float getVx() { return this->vx; }
	void setVx(float vx) { this->vx = vx; }
	float getVy() { return this->vy; }
	void setVy(float vy) { this->vy = vy; }
	void setDx(float dx) { this->dx = dx; }
	float getDx() { return this->dx; }
	void setDy(float dy) { this->dy = dy; }
	float getDy() { return this->dy; }
	bool getDirRight() { return this->isDirRight; }
	void setDirRight(bool dir) { this->isDirRight = dir; }

	void setAni(int ani) { 
		this->ani = ani; 
		//animation_set->at(ani)->setCurrentFrame(0);
	}
	int getAni() { return this->ani; }

	void setIsLastAni(bool isLastAni) { this->isLastAni = isLastAni; }
	int getIsLastAni() { return this->isLastAni; }

	void setStatus(int status) { this->status = status; }
	int getStatus() { return this->status; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() {};

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void RenderBoundingBox(int alpha);

	CGameObject();
	~CGameObject();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	void release();

	vector<DongCotGrid> getDsGrid();
	void updateGrid();

};