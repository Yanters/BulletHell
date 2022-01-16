#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

#include "game.h"


// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
	int actualLevelMain = 0;

	while (1) {
		Game MainGame;
		MainGame.actualLevel = actualLevelMain;
		MainGame.pickLevel();
		MainGame.setLevel();
		if (MainGame.UpdateTime()) {
			break;
		}
		actualLevelMain = MainGame.actualLevel;
	}

	return 0;
};
