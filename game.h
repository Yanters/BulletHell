#pragma once
#include<math.h>
#include<stdio.h>
#include<string.h>

#include "player.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#define LEVEL_WIDTH    1280 
#define LEVEL_HEIGHT   1078

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);


class game {
public:
	int t1, t2, quit, frames, rc;
	double delta, worldTime, fpsTimer, fps, distance, etiSpeed;
	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* eti;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	player player;

	char text[128];
	int czarny;
	int zielony;
	int czerwony;
	int niebieski;
	//functions
	game();

	void DrawString(int x, int y, const char* text);
	void DrawSurface(SDL_Surface* sprite, int x, int y);
	void DrawLine(int x, int y, int l, int dx, int dy, Uint32 color);
	void DrawRectangle(int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
	SDL_Surface* LoadImage(char imageName[]);
	void UpdateTime();
	void QuitGame();
	void CheckInput();
};