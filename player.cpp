#include "player.h"

player::player() {
	speed = 300;
	VelX = 0, VelY = 0;
	positionX = SCREEN_WIDTH / 2 - 130;
	positionY = LEVEL_HEIGHT / 2;
}

void player::movePlayer(double delta) {

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
	else if (positionY> LEVEL_HEIGHT - (PLAYER_HEIGHT/2)) {
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