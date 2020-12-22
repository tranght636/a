#include "TileMap.h"

#include<fstream>
using namespace std;

TileMap* TileMap::instance = NULL;

TileMap* TileMap::getInstance() {
	if (instance == NULL) {
		instance = new TileMap();
	}
	return instance;
}

void TileMap::render(Camera * camera)
{
	int tileLeft, tileRight, tileTop, tileBottom;
	tileLeft = camera->getLeft() / tileWidth;
	tileRight = camera->getRight() / tileWidth;
	tileTop = camera->getTop() / tileHeight;
	tileBottom = camera->getBottom() / tileHeight;

	if (tileLeft < 0)
	{
		tileLeft = 0;
	}
	if (tileTop < 0)
	{
		tileTop = 0;
	}
	if (tileRight >= tileColumns)
	{
		tileRight = tileColumns - 1;
	}
	if (tileBottom >= tileRows)
	{
		tileBottom = tileRows - 1;
	}
	for (size_t rowIndex = tileTop; rowIndex <= tileBottom; rowIndex++)
	{
		for (size_t columnIndex = tileLeft; columnIndex <= tileRight; columnIndex++)
		{
			int xWorldOfTile = columnIndex * tileWidth;
			int yWorldOfTile = rowIndex * tileHeight;
			int tileValue = matrix[rowIndex][columnIndex];
			int left = tileWidth * (tileValue % tilesheetColumns);
			int top = tileHeight * (tileValue / tilesheetColumns);
			int right = left + tileWidth;
			int bottom = top + tileHeight;
 			CWindow::GetInstance()->Draw(xWorldOfTile, yWorldOfTile, texture, left, top, right, bottom);
		}
	}
}

int TileMap::getMapHeight()
{
	return mapHeight;
}

int TileMap::getMapWidth() {
	return mapWidth;
}

void TileMap::init(LPCWSTR pathImage, LPCWSTR pathInfo)
{
	texture = CWindow::GetInstance()->LoadTexture(pathImage);
	fstream fs(pathInfo);
	fs >> tileRows >> tileColumns >> tileWidth >> tileHeight >> tilesheetColumns;
	this->mapHeight = tileRows * tileHeight;
	this->mapWidth = tileColumns * tileWidth;
	matrix = new int*[tileRows];
	for (size_t rowIndex = 0; rowIndex < tileRows; rowIndex++)
	{
		matrix[rowIndex] = new int[tileColumns];
		for (size_t columnIndex = 0; columnIndex < tileColumns; columnIndex++)
		{
			fs >> matrix[rowIndex][columnIndex];
		}
	}
}

void TileMap::clear() {
	for (int i = 0; i < tileRows; i++) {
		delete matrix[i];
	}
	delete matrix;
}

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
}
