#pragma once

#define PLAYER_WIDTH   60
#define PLAYER_HEIGHT  77

#include "common.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}


class player {
public:
	player();

	SDL_Surface* sprite;
	SDL_Surface* heroR;
	SDL_Surface* heroL;


	SDL_Surface* bulletSprite;

	int speed, VelX, VelY;
	double  positionX, positionY;
	double offsetX=0, offsetY=0;
	void movePlayer(double delta);
	int direction = 0;
	void switchPlayer();

	Bullet bullets[100];
	int bulletsShoot = 0;

	double bulletSpeed = 0.7;
	
	double shootCooldown = 0.5;
	double lastShoot= shootCooldown;

	void calculateOffset();
	void shootBullet(double velX, double velY);
};