#include "common.h"

SDL_Surface* LoadImage(char imageName[]) {
	// wczytanie obrazka cs8x8.bmp
	SDL_Surface* image;
	image = SDL_LoadBMP(imageName);
	/*if (image == NULL) {
		printf("SDL_LoadBMP(%s) error: %s\n", imageName, SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	};*/
	return image;
}

void Bullet::calcBullet() {
	if (alive) {
		positionX += velX * speed;
		positionY += velY * speed;
	}

	if (positionX < 0 || positionX > LEVEL_WIDTH || positionY < 0 || positionY > LEVEL_HEIGHT) {
		alive = false;
	}
}


bool Bullet::checkCollision(double ObjectPositionX, double ObjectPositionY, int ObjectWidth, int ObjectHeight) {
	if (positionX >= ObjectPositionX - (ObjectWidth / 2) && positionX <= ObjectPositionX + (ObjectWidth / 2) && positionY>= ObjectPositionY - (ObjectHeight/2) && positionY <= ObjectPositionY + (ObjectHeight / 2)) {
		return true;
	}
	else {
		return false;
	}

}