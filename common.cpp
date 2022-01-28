#include "common.h"

SDL_Surface* LoadImage(char imageName[]) {
	// wczytanie obrazka cs8x8.bmp
	SDL_Surface* image;
	image = SDL_LoadBMP(imageName);
	return image;
}

void Bullet::calcBullet(double deltaTime) {
	if (alive) {
		positionX += velX * speed * deltaTime;
		positionY += velY * speed * deltaTime;
	}

	if (positionX < 0 || positionX > LEVEL_WIDTH || positionY < 0 || positionY > LEVEL_HEIGHT) {
		alive = false;
	}
}


bool Bullet::checkCollision(double ObjectPositionX, double ObjectPositionY, int ObjectWidth, int ObjectHeight) {
	if (positionX >= ObjectPositionX - (ObjectWidth / 2) && positionX <= ObjectPositionX + (ObjectWidth / 2) && positionY >= ObjectPositionY - (ObjectHeight / 2) && positionY <= ObjectPositionY + (ObjectHeight / 2)) {
		return true;
	}
	else {
		return false;
	}

}