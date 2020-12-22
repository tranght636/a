#pragma once
#include <unordered_map>
#include <d3dx9.h>
#include <Windows.h>
#include <d3d9.h>

#include "debug.h"
#include "CWindow.h"

using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	static CTextures * __instance;

	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public:
	
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor = 0);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);
	static CTextures * GetInstance();
	void Clear();
	CTextures();
	~CTextures();
};