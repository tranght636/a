#include "GameObject.h"
#include <algorithm>
#include "CWindow.h"
#include "PlayScence.h"
#include "Thang.h"

#include "Grid.h"
#include "QuanLyGrid.h"

//unordered_map<int, LPANIMATION> CGameObject::animations;

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
	ani = -1;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	this->dx = vx * dt;
	this->dy = vy * dt;
}

//void CGameObject::AddAnimation(int aniId)
//{
//	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
//	animations[aniId] = ani;
//}


/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	svx = coO->getVx();
	svy = coO->getVy();

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	Collision::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Thang*>(coObjects->at(i))) continue;
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty,
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

void CGameObject::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CGameObject::RenderBoundingBox(int alpha)
{
	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;
	CWindow::GetInstance()->Draw(x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 0, 0, alpha);
}


CGameObject::~CGameObject()
{
}

void CGameObject::release() {
	/*CPlayScene::removeObject(this);
	delete this;*/
	this->isDelete = true;
	QuanLyGrid::getInstance()->addObjectToDelete(this);
}

vector<DongCotGrid> CGameObject::getDsGrid() {
	QuanLyGrid::getInstance();
	vector<DongCotGrid> kq;
	kq.clear();

	float gioiHanGridTrai = this->x / QuanLyGrid::widthGrid;
	float gioiHanGridPhai = (this->x + this->width) / QuanLyGrid::widthGrid;
	float gioiHanGridTren = this->y / QuanLyGrid::heightGrid;
	float gioiHanGridDuoi = (this->y + this->height) / QuanLyGrid::heightGrid;

	for (int i = gioiHanGridTrai; i <= gioiHanGridPhai; i++) {
		for (int j = gioiHanGridTren; j <= gioiHanGridDuoi; j++) {
			DongCotGrid dc;
			dc.d = j;
			dc.c = i;
			kq.push_back(dc);
		}
	}

	return kq;
}

void CGameObject::updateGrid() {
	// remove
	for (int i = 0; i < this->dsGrid.size(); i++) {
		DongCotGrid dc = this->dsGrid.at(i);
		Grid* grid = QuanLyGrid::getInstance()->getGrid(dc.d, dc.c);
		grid->removeObject(this);
	}
	this->dsGrid.clear();

	vector<DongCotGrid> dongCotGrid = this->getDsGrid();
	for (int i = 0; i < dongCotGrid.size(); i++) {
		DongCotGrid dc = dongCotGrid.at(i);

		this->dsGrid.push_back(dc);

		Grid* grid = QuanLyGrid::getInstance()->getGrid(dc.d, dc.c);
		grid->addObject(this);
	}
}