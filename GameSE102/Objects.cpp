#include "Objects.h"

Objects* Objects::instance = NULL;

Objects* Objects::GetInstance()
{
	if (instance == NULL) instance = new Objects();
	return instance;
}

void Objects::addObject(LPGAMEOBJECT object) {
	this->objects.push_back(object);
}

vector<LPGAMEOBJECT> Objects::getAllObjects() {
	return this->objects;
}

Objects::Objects()
{
}


Objects::~Objects()
{
}
