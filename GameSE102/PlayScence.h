#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Stair.h"

class CPlayScene : public CScene
{
protected:
	CPlayer* player;					// A play scene has to have player, right? 

	

	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP(string line);
	void _ParseSection_CAMERA(string line);
	void parseSentionKhongGian(string line);

public:
	static vector<LPGAMEOBJECT> listObject;
	static vector<LPGAMEOBJECT> objects;
	static void removeObject(LPGAMEOBJECT gameObject);
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CPlayer * GetPlayer() { return player; }

	static void addObjectToGrid(LPGAMEOBJECT object);
};


