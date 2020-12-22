#pragma once
#include <Windows.h>
#include "Objects.h"
#include "CPlayer.h"
#include "Textures.h"
#include "TileMap.h"
#include "Brick.h"
#include "Scence.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class CGame
{
	static CGame * __instance;
	int screen_width;
	int screen_height;

	unordered_map<int, LPSCENE> scenes;
	int current_scene;

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_LAYER(string line);
public:
	static CGame * GetInstance();
	void Load(LPCWSTR gameFile);
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	int getCurrentSceneIndex() { return current_scene; }
	void SwitchScene(int scene_id);
	int GetScreenWidth() { return screen_width; }
	int GetScreenHeight() { return screen_height; }
	void loadSceneWhenPlayerDie();
	CGame();
	~CGame();
};


