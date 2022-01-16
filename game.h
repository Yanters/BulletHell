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
class Healing {
public:
	Healing();
	double positionX, positionY;
	bool active = false;
	bool checkCollision(double ObjectPositionX, double ObjectPositionY, int ObjectWidth, int ObjectHeight);
};

class Game {
public:
	int t1, t2, quit, frames, rc;
	double delta, worldTime, fpsTimer, fps, distance, etiSpeed;
	SDL_Event event;
	SDL_Surface* screen, * charset, * background, * menu, * victory, * defeat, * healing, * markA, * markB, * markC;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	Player player;
	Boss boss;

	char text[128];
	int czarny;
	int zielony;
	int czerwony;
	int niebieski;
	int score = 0;

	Game();
	void pickLevel();
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
	void displayHP(double pX, double pY, int pHealth, int pMaxHealth, double bX, double bY, int bHealth, int bMaxHealth, int bWidth, int bHeight, double offsetX, double offsetY);
	void spawnAndAddHP(double deltaTime);
	double spawnHpCooldown = 5.0;
	double lastSpawnHpTime = 0;
	int maxSpawnHp = 5;
	int spawnedHpCount = 0;
	Healing healingBox[5];

	int actualLevel = 1;
	void displayDefeat();
	void displayVictory();
	void checkGameStatus();
};