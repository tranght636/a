#pragma once

/* Window Game */
#define SCREEN_WIDTH 270
#define SCREEN_HEIGHT 282
#define WINDOW_CLASS_NAME L"GameSE104"
#define MAX_FRAME_RATE 90
#define SENCE_CONFIG_PATH L"scene-config.txt"
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

/* ID Texture */
#define ID_TEX_PLAYER 3
#define ID_TEX_BBOX -100

/* Camera */
#define SCREEN_WIDTH_1_2 (SCREEN_WIDTH / 2 - 16)
#define SCREEN_HEIGHT_1_4 (SCREEN_HEIGHT / 4)
#define SCREEN_HEIGHT_1_2 (SCREEN_HEIGHT / 2)

#define SCREEN_DY	(SCREEN_HEIGHT / 2 - 16)
#define SCREEN_DY_4	(SCREEN_HEIGHT / 2.3)
