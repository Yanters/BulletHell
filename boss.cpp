#include "boss.h"

Boss::Boss(char name[], double setPositionX, double setPositionY) {
	sprite = LoadImage(name);
	positionX = setPositionX;
	positionY = setPositionY;
	bulletSprite = LoadImage("./images/bullet.bmp");

}

void Boss::startAttack(double timeDiff) {
	srand(time(NULL));
	int randomNumber = rand() % 2 + 1;
	 
	if (lastShoot >= shootCooldown) {
		lastShoot = 0;
		switch (type)
		{
		case 1:
			if (randomNumber == 1) {
				simplePattern();
			}
			else if (randomNumber == 2) {
				diagnalPattern();
			}
			break;
		case 2:
			if (int(timeDiff) % 5 == 0)
			{
				simplePattern();
				diagnalPattern();
			}
			else {
				spiralPattern(timeDiff);
			}
			break;
		case 3:
			if (int(timeDiff)%5==0)
			{
				multipleSpiralPattern(-timeDiff);

			}
			else {
				multipleSpiralPattern(timeDiff);
			}
			break;
		}
		
	}
	
	
	
}

void Boss::shootBullet(double velX, double velY) {
	
		if (bulletsShoot == 100) bulletsShoot = 0;
		bullets[bulletsShoot].alive = true;
		bullets[bulletsShoot].positionX = positionX;
		bullets[bulletsShoot].positionY = positionY;
		bullets[bulletsShoot].velX = velX;
		bullets[bulletsShoot].velY = velY;
		bullets[bulletsShoot].speed = bulletSpeed;
		bulletsShoot++;

}

void Boss::simplePattern() {
	for (int i = 0; i < 4; i++) {
		switch (i)
		{
		case 0:
			shootBullet(1, 0);
			break;
		case 1:
			shootBullet(-1, 0);
			break;
		case 2:
			shootBullet(0, 1);
			break;
		case 3:
			shootBullet(0, -1);
			break;
		}
	}
}

void Boss::diagnalPattern() {
	for (int i = 0; i < 4; i++) {
		switch (i)
		{
		case 0:
			shootBullet(1, 1);
			break;
		case 1:
			shootBullet(-1, -1);
			break;
		case 2:
			shootBullet(-1, 1);
			break;
		case 3:
			shootBullet(1, -1);
			break;
		}
	}
}

void Boss::spiralPattern(double timeDiff) {
	shootBullet(sin(M_PI * timeDiff), cos(M_PI * timeDiff));
}

void Boss::multipleSpiralPattern(double timeDiff) {

		shootBullet(sin(M_PI * timeDiff), cos(M_PI * timeDiff));
		shootBullet(sin(M_PI * timeDiff +M_PI), cos(M_PI * timeDiff + M_PI));

}