#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
using namespace std;

#define ANI_DEFAUT_TIME 100

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;
	int achorX;
	int achorY;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int achorX = -1, int achorY = -1);
	int getWidth();
	int getHeight();
	void Draw(float x, float y, int alpha = 255);
	int getAchorX() { return this->achorX; }
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int achorX, int achorY);
	LPSPRITE Get(int id);
	void Clear();
	static CSprites * GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
	void render(float x, float y, bool isDirRight = true);
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	int id;
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	int nextFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	void setId(int id) { this->id = id; }
	int getId() { this->id; }
	CAnimation(int defaultTime = ANI_DEFAUT_TIME);
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, bool isDirRight = true, int alpha = 255);
	LPANIMATION_FRAME getCurrentFrame();
	LPANIMATION_FRAME getFrame(int frame) { return frames[frame]; }
	LPANIMATION_FRAME getNextFrame();
	void setCurrentFrame(int currentFrame) { this->currentFrame = currentFrame; }
	int getCurrentFrameIndex() { return currentFrame == -1 ? 0 : currentFrame; }
};

typedef CAnimation* LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void Clear();
	static CAnimations * GetInstance();
};


typedef vector<LPANIMATION> CAnimationSet;

typedef CAnimationSet* LPANIMATION_SET;

/*
	Manage animation set database
*/
class CAnimationSets
{
	static CAnimationSets * __instance;

	unordered_map<int, LPANIMATION_SET> animation_sets;

public:
	CAnimationSets();
	void Add(int id, LPANIMATION_SET ani);
	LPANIMATION_SET Get(unsigned int id);


	static CAnimationSets * GetInstance();
};

