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
	SDL_Surface* heroR, * heroRS;
	SDL_Surface* heroL, * heroLS;


	SDL_Surface* bulletSprite;

	int speed, VelX, VelY;
	double  positionX, positionY;
	double offsetX=0, offsetY=0;
	void movePlayer(double delta);
	int direction = 0;
	void switchPlayer();
	int health = 5;

	int pWidth = PLAYER_WIDTH;
	int pHeight = PLAYER_HEIGHT;
	Bullet bullets[100];
	int bulletsShoot = 0;

	double bulletSpeed = 0.7;
	
	double shootCooldown = 0.5;
	double lastShoot= shootCooldown;

	double barrierCooldown = 5;
	double lastBarrier = barrierCooldown;
	double safeCooldown = 1;
	double lastTimeSafe = 0;
	bool isSafe = false;

	void calculateOffset();
	void shootBullet(double velX, double velY);

	void hitPlayer();
	void keepSafe(double delta);
};