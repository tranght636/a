#include "Sprites.h"
#include "debug.h"
#include "CWindow.h"
#include "DirectionTexture.h"


CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int achorX, int achorY)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
	this->achorX = achorX;
	this->achorY = achorY;
}

int CSprite::getWidth() {
	return right - left;
}

int CSprite::getHeight() {
	return bottom - top;
}



void CSprite::Draw(float x, float y, int alpha)
{
	CWindow::GetInstance()->Draw(x, y, texture, left, top, right, bottom, achorX, achorY, alpha);
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}



void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int achorX, int achorY)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex, achorX, achorY);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

void CAnimationFrame::render(float x, float y, bool isDirRight) {
	if (!isDirRight) {
		DirectionTexture::getInstance()->SetDirection(false, x, this->sprite->getWidth(), this->sprite->getWidth());
	}
	this->sprite->Draw(x, y);
	DirectionTexture::getInstance()->SetDirection(true, x, this->sprite->getWidth(), this->sprite->getWidth());
}

CAnimation::CAnimation(int defaultTime) {
	this->defaultTime = defaultTime;
	lastFrameTime = -1; 
	currentFrame = -1;
}

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	if (sprite == NULL)
	{
		DebugOut(L"[ERROR] Sprite ID %d cannot be found!\n", spriteId);
	}
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, bool isDirRight, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			
			if (currentFrame >= frames.size()) {
				currentFrame = 0;
			}
		}
	}
	
	LPANIMATION_FRAME frame = frames[currentFrame];
	LPANIMATION_FRAME frame2 = frames[0];
	float width = frame2->GetSprite()->getWidth() - (frame2->GetSprite()->getAchorX() < 0 ? 0 : frame2->GetSprite()->getAchorX());
	if (!isDirRight) {
		DirectionTexture::getInstance()->SetDirection(false, x, frame->GetSprite()->getWidth(), width);
	}
	frame->GetSprite()->Draw(x, y, alpha);
	DirectionTexture::getInstance()->SetDirection(true, x, frame->GetSprite()->getWidth(), width);

}

LPANIMATION_FRAME CAnimation::getCurrentFrame() {
	
	return frames[currentFrame == -1 ? 0 : currentFrame];
}

LPANIMATION_FRAME CAnimation::getNextFrame() {
	if(frames.size() > 1)
		return frames[nextFrame];
	return 0;
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	ani->setId(id);
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}

void CAnimations::Clear()
{
	for (auto x : animations)
	{
		LPANIMATION ani = x.second;
		delete ani;
	}

	animations.clear();
}

/*
	Clear all loaded textures
*/
void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}

CAnimationSets::CAnimationSets()
{

}

CAnimationSets * CAnimationSets::__instance = NULL;

CAnimationSets *CAnimationSets::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimationSets();
	return __instance;
}

LPANIMATION_SET CAnimationSets::Get(unsigned int id)
{
	LPANIMATION_SET ani_set = animation_sets[id];
	if (ani_set == NULL)
		DebugOut(L"[ERROR] Failed to find animation set id: %d\n", id);

	return ani_set;
}

void CAnimationSets::Add(int id, LPANIMATION_SET ani_set)
{
	animation_sets[id] = ani_set;
}
