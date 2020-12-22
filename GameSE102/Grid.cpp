#include "Grid.h"
#include <algorithm>
using namespace std;

void Grid::removeObject(LPGAMEOBJECT object) {
	this->objects.erase(remove(this->objects.begin(), this->objects.end(), object), this->objects.end());
}


void Grid::addObject(LPGAMEOBJECT object) {
	for (int i = 0; i < this->objects.size(); i++) {
		if (this->objects.at(i) == object) {
			return;
		}
	}
	this->objects.push_back(object);
}

void Grid::thucThiDelete() {
	for (int i = 0; i < this->objects.size(); i++) {
		if (this->objects.at(i)->getIsDelete()) {
			LPGAMEOBJECT obj = this->objects.at(i);
			this->removeObject(obj);
			i -= 1;
		}
	}
}
