#pragma once


#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#define LEVEL_WIDTH    1280 
#define LEVEL_HEIGHT   1078

#define PLAYER_WIDTH   60
#define PLAYER_HEIGHT  77


extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}


class player {
public:
	player();

	int speed, VelX, VelY;
	double  positionX, positionY;
	double offsetX=0, offsetY=0;
	void movePlayer(double delta);
	void calculateOffset();
};