#pragma once


#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}


class player {
public:
	player();

	int speed, VelX, VelY, positionX, positionY;
	void movePlayer();
};