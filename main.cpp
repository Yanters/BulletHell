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


	while (1) {
		Game MainGame;
		MainGame.pickLevel();
		MainGame.setLevel();
		if (MainGame.UpdateTime()) {
			break;
		}
	}
	// okno konsoli nie jest widoczne, je¿eli chcemy zobaczyæ
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieniæ na "Console"
	// console window is not visible, to see the printf output
	// the option:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// must be changed to "Console"
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	return 0;
	};
