#pragma once
#include "CWindow.h"
#include "Sprites.h"
#include "Camera.h"


class TileMap
{
	int tileWidth;
	int tileHeight;
	int tileRows;
	int tileColumns;
	int tilesheetColumns;
	int mapHeight;
	int mapWidth;
	
	int** matrix;
	LPDIRECT3DTEXTURE9 texture;
	static TileMap* instance;
public:
	static TileMap* getInstance();
	int getMapHeight();
	int getMapWidth();
	void init(LPCWSTR pathImage, LPCWSTR pathInfo);
	void render(Camera* camera);
	void clear();
	TileMap();
	~TileMap();
};

