#include "player.h"

player::player() {
	speed = 5;
	VelX = 0, VelY = 0;
	positionX = SCREEN_WIDTH / 2;
	positionY = SCREEN_HEIGHT / 2;
}

void player::movePlayer() {
	positionX += VelX * speed;
	positionY += VelY * speed;
}