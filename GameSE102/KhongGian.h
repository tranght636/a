#pragma once
class KhongGian
{
private:
	int id;

	float left;
	float top;
	float right;
	float bottom;

	float xPlayer;
	float yPlayer;

public:

	KhongGian();
	~KhongGian();

	KhongGian(int id, float l, float t, float r, float b);

	int getId() { return id; }
	float getLeft() { return left; }
	float getTop() { return top; }
	float getRight() { return right; }
	float getBottom() { return bottom; }
	float getHeight() { return this->bottom - this->top; }
};

