#include "DirectionTexture.h"

DirectionTexture* DirectionTexture::instance = NULL;

DirectionTexture* DirectionTexture::getInstance() {
	if (instance == NULL) {
		instance = new DirectionTexture();
	}
	return instance;
}

void DirectionTexture::SetDirection(bool isDirRight, int x, int widthCurrent, int width) {
	D3DXMATRIX flipMatrix;
	D3DXMatrixIdentity(&flipMatrix);
	if (!isDirRight) {
		flipMatrix._11 = -1;
		flipMatrix._41 = 2 * (x - Camera::getInstance()->getX() + widthCurrent / 2) - widthCurrent + width;
	}
	CWindow::GetInstance()->GetSpriteHandler()->SetTransform(&flipMatrix);
}

DirectionTexture::DirectionTexture()
{
}


DirectionTexture::~DirectionTexture()
{
}
