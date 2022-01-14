#pragma once
#include<math.h>
#include<stdio.h>
#include<string.h>

#include "common.h"
#include "player.h"
#include "boss.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);


class Game {
public:
	int t1, t2, quit, frames, rc;
	double delta, worldTime, fpsTimer, fps, distance, etiSpeed;
	SDL_Event event;
	SDL_Surface* screen, * charset, * background ,* menu;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	player player;
	Boss boss;

	char text[128];
	int czarny;
	int zielony;
	int czerwony;
	int niebieski;
	//functions
	Game();
	void pickLevel();
	int pickedLevel = 1;
	void setLevel();
	void displayMenu();

	void DrawString(int x, int y, const char* text);
	void DrawSurface(SDL_Surface* sprite, int x, int y);
	void DrawLine(int x, int y, int l, int dx, int dy, Uint32 color);
	void DrawRectangle(int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
	bool UpdateTime();
	void QuitGame();
	void CheckInput();
	void displayInterface();
};