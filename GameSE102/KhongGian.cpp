#include "KhongGian.h"



KhongGian::KhongGian()
{
}


KhongGian::~KhongGian()
{
}

KhongGian::KhongGian(int id, float l, float t, float r, float b) {
	this->id = id;
	this->left = l;
	this->top = t;
	this->right = r;
	this->bottom = b;
}
