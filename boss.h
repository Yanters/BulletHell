#pragma once


#include "common.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}


class Boss {
public:
	Boss(char name[] = "./images/boss1.bmp", double setPositionX = LEVEL_WIDTH / 2 + 100, double setPositionY = LEVEL_HEIGHT / 2);
	SDL_Surface* sprite = LoadImage("./images/boss1.bmp");
	int BOSS_WIDTH = 200, BOSS_HEIGHT=173;
	SDL_Surface* bulletSprite;

	double positionX = LEVEL_WIDTH/2, positionY= LEVEL_HEIGHT / 2;
	int type = 1;
	int bWidth;
	int bHeight;
	int maxHealth = 50;
	int health = maxHealth;

	Bullet bullets[200];
	int bulletsShoot = 0;

	double bulletSpeed = 0.7;
	bool canMove = false;
	double bossSpeed = 1;

	double shootCooldown = 0.5;
	double lastShoot = shootCooldown;

	void startAttack(double timeDiff);

	void shootBullet(double velX, double velY);
	//patterns
	void simplePattern();
	void diagnalPattern();
	void spiralPattern(double timeDiff);
	void multipleSpiralPattern(double timeDiff);
	void moveBoss(double timeDelta, double distance);
};