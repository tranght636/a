#include "Delay.h"

bool Delay::delay(int ms) {
	if (isStart) {
		timeStart = GetTickCount();
		isStart = false;
	}

	DWORD now = GetTickCount();

	if (now - timeStart > ms) {
		isStart = true;
		return true;
	}

	return false;
}