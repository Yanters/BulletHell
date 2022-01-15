#pragma once

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include <stdlib.h>     /* srand, rand */
#include <time.h> 

#define _USE_MATH_DEFINES

#define LEVEL_WIDTH    1920 
#define LEVEL_HEIGHT   1080

#define SCREEN_WIDTH	900
#define SCREEN_HEIGHT	600

SDL_Surface* LoadImage(char imageName[]);

class Bullet {
public:
	double velX = 1;
	double velY = 1;
	double speed = 10;
	double positionX, positionY;
	bool alive = false;
	void calcBullet();
	bool checkCollision(double ObjectPositionX, double ObjectPositionY, int ObjectWidth, int ObjectHeight);
};

