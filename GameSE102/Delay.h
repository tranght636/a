#pragma once
#include <Windows.h>

class Delay
{
	bool isStart = true;
	DWORD timeStart;
public:
	bool delay(int ms);
};