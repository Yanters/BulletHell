#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

#include "game.h"


// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {
	int actualLevelMain = 0;

	while (1) {
		Game MainGame;
		MainGame.actualLevel = actualLevelMain;
		MainGame.pickLevel();
		MainGame.setLevel();
		if (MainGame.UpdateTime()) {
			break;
		}

		//if (MainGame.actualLevel == 1) {
		//	actualLevelMain = 1;
		//}
		//else {
			actualLevelMain = MainGame.actualLevel;
		//}
	}
	// okno konsoli nie jest widoczne, je�eli chcemy zobaczy�
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieni� na "Console"
	// console window is not visible, to see the printf output
	// the option:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// must be changed to "Console"
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	return 0;
	};
