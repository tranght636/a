#include "Brick.h"
#include "Game.h"
#include<fstream>

Brick* Brick::instance = NULL;

Brick* Brick::getInstance() {
	if (instance == NULL) {
		instance = new Brick();
	}
	return instance;
}

Brick::Brick(float x, float y, float width, float height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Brick::Brick()
{
}


Brick::~Brick()
{
}
