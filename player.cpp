#include "player.h"

player::player() {
	speed = 300;
	VelX = 0, VelY = 0;
	positionX = SCREEN_WIDTH / 2 - 275;
	positionY = LEVEL_HEIGHT / 2;
	direction = 0;
	heroR = LoadImage("./images/hero.bmp");
	heroL = LoadImage("./images/hero2.bmp");
	sprite = heroR;
	bulletSprite = LoadImage("./images/bullet2.bmp");
}

void player::switchPlayer() {
	if (direction == 0) {
		sprite = heroR;
	}
	else if (direction == 1) {
		sprite = heroL;
	}
}


void player::movePlayer(double delta) {
	switchPlayer();
	positionX += double((VelX * speed) * delta);
	positionY += double((VelY * speed) * delta);

	calculateOffset();

	if (positionX < PLAYER_WIDTH / 2) {
		positionX = PLAYER_WIDTH / 2;
	}
	else if (positionX > LEVEL_WIDTH - (PLAYER_WIDTH / 2))
	{
		positionX = LEVEL_WIDTH - PLAYER_WIDTH / 2;
	}

	if (positionY < PLAYER_HEIGHT / 2) {
		positionY = PLAYER_HEIGHT / 2;
	}
	else if (positionY > LEVEL_HEIGHT - (PLAYER_HEIGHT / 2)) {
		positionY = LEVEL_HEIGHT - PLAYER_HEIGHT / 2;
	}

}



void player::calculateOffset() {
	if (positionX > SCREEN_WIDTH / 2 && positionX < LEVEL_WIDTH - (SCREEN_WIDTH / 2)) {
		offsetX = SCREEN_WIDTH / 2 - positionX;
	}
	else if (positionX >= LEVEL_WIDTH - (SCREEN_WIDTH / 2)) {
		offsetX = SCREEN_WIDTH - LEVEL_WIDTH;
	}
	else {
		offsetX = 0;
	}

	if (positionY > SCREEN_HEIGHT / 2 && positionY < LEVEL_HEIGHT - (SCREEN_HEIGHT / 2)) {
		offsetY = SCREEN_HEIGHT / 2 - positionY;
	}
	else if (positionY >= LEVEL_HEIGHT - (SCREEN_HEIGHT / 2)) {
		offsetY = SCREEN_HEIGHT - LEVEL_HEIGHT;
	}
	else {
		offsetY = 0;
	}
}

void player::shootBullet(double velX, double velY) {
	if (lastShoot >= shootCooldown) {
		lastShoot = 0;
		if (bulletsShoot == 100) bulletsShoot = 0;
		bullets[bulletsShoot].alive = true;
		bullets[bulletsShoot].positionX = positionX;
		bullets[bulletsShoot].positionY = positionY;
		bullets[bulletsShoot].velX = velX;
		bullets[bulletsShoot].velY = velY;
		bullets[bulletsShoot].speed = bulletSpeed;
		bulletsShoot++;
	}

}