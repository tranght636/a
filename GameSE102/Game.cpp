#include <iostream>
#include <fstream>

#include "Game.h"
#include "Utils.h"
#include "PlayScence.h"
#include "PlayerXe.h"
#include "PlayerNguoi.h"
#include "PlayerNguoi2.h"
#include "QuanLyKhongGian.h"


CGame * CGame::__instance = NULL;

CGame *CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}

CGame::CGame()
{

}

CGame::~CGame()
{

}

#define MAX_GAME_LINE 10000


#define GAME_FILE_SECTION_UNKNOWN	-1
#define GAME_FILE_SECTION_SETTINGS	1
#define GAME_FILE_SECTION_SCENES 2
#define SCENE_SECTION_TEXTURES	3
#define SCENE_SECTION_SPRITES	4
#define SCENE_SECTION_ANIMATIONS 5
#define SCENE_SECTION_ANIMATION_SETS	6
#define SCENE_SECTION_PLAYER	7

void CGame::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start")
		current_scene = atoi(tokens[1].c_str());
	else
		DebugOut(L"[ERROR] Unknown game setting %s\n", ToWSTR(tokens[0]).c_str());
}

void CGame::_ParseSection_SCENES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	int id = atoi(tokens[0].c_str());
	LPCWSTR path = ToLPCWSTR(tokens[1]);

	LPSCENE scene = new CPlayScene(id, path);
	scenes[id] = scene;
}

void CGame::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CGame::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());
	int achorX = 0, achorY = 0;
	if (tokens.size() == 8) {
		achorX = atoi(tokens[6].c_str());
		achorY = atoi(tokens[7].c_str());
	}

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex, achorX, achorY);
}

void CGame::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	/*DebugOut(L"--> %s\n",ToWSTR(line).c_str());*/

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());

	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CGame::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void CGame::_ParseSection_LAYER(string line) {
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	int id = atoi(tokens[0].c_str());

	int aniSetId = atoi(tokens[1].c_str());
	LPANIMATION_SET animation_sets = CAnimationSets::GetInstance()->Get(aniSetId);

	if (id == 1) {
		float xPlayer = atoi(tokens[2].c_str());
		float yPlayer = atoi(tokens[3].c_str());
		PlayerXe::getInstance()->setX(xPlayer);
		PlayerXe::getInstance()->setY(yPlayer);
		PlayerXe::getInstance()->setStart(xPlayer, yPlayer);
		PlayerXe::getInstance()->SetAnimationSet(animation_sets);
	}
	else if (id == 2) {
		PlayerNguoi::getInstance()->SetAnimationSet(animation_sets);
	}
	else if (id == 3) {
		PlayerNguoi2::getInstance()->SetAnimationSet(animation_sets);
	}
}


/*
	Load game campaign file and load/initiate first scene
*/
void CGame::Load(LPCWSTR gameFile)
{
	DebugOut(L"[INFO] Start loading game file : %s\n", gameFile);

	ifstream f;
	f.open(gameFile);
	char str[MAX_GAME_LINE];

	// current resource section flag
	int section = GAME_FILE_SECTION_UNKNOWN;

	while (f.getline(str, MAX_GAME_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") { section = GAME_FILE_SECTION_SETTINGS; continue; }
		if (line == "[SCENES]") { section = GAME_FILE_SECTION_SCENES; continue; }
		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") { section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[PLAYER]") { section = SCENE_SECTION_PLAYER; continue; }
		
		switch (section)
		{
		case GAME_FILE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case GAME_FILE_SECTION_SCENES: _ParseSection_SCENES(line); break;
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_PLAYER: _ParseSection_LAYER(line); break;
		}
	}
	f.close();

	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", gameFile);

	SwitchScene(current_scene);
}

void CGame::SwitchScene(int scene_id)
{
	DebugOut(L"[INFO] Switching to scene %d\n", scene_id);

	scenes[current_scene]->Unload();

	current_scene = scene_id;
	LPSCENE s = scenes[scene_id];
	s->Load();
}

void CGame::loadSceneWhenPlayerDie() {
	this->SwitchScene(CGame::GetInstance()->getCurrentSceneIndex());

	CPlayer::getInstance()->setPlayerHienTai(PLAYER_XE);

	PlayerXe* player = PlayerXe::getInstance();
	player->SetPosition(1073, 1164);
	player->setDirRight(true);
	player->setMau(MAU);
	player->setStatus(STATUS_BINH_THUONG);

	Camera::getInstance()->setX(1024);
	Camera::getInstance()->setY(1035);

	QuanLyKhongGian::getInstance()->setKhongGianHienTaiId(1);
}