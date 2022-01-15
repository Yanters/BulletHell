#include "game.h"

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
	}

	// tryb pe³noekranowy / fullscreen mode
//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
//	                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Bullet Hell");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	menu = LoadImage("./images/menu.bmp");
	background = LoadImage("./images/background.bmp");
	victory = LoadImage("./images/victory.bmp");
	defeat = LoadImage("./images/defeat.bmp");
	charset = LoadImage("./cs8x8.bmp");
	SDL_SetColorKey(charset, true, 0x000000);




	t1 = SDL_GetTicks();



}




// narysowanie napisu txt na powierzchni screen, zaczynaj¹c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj¹ca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images

void Game::DrawString( int x, int y, const char* text) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt œrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void Game::DrawSurface(SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};



// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};


// rysowanie linii o d³ugoœci l w pionie (gdy dx = 0, dy = 1) 
// b¹dŸ poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void Game::DrawLine(int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};



// rysowanie prostok¹ta o d³ugoœci boków l i k
// draw a rectangle of size l by k
void Game::DrawRectangle( int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine( x, y, k, 0, 1, outlineColor);
	DrawLine( x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine( x, y, l, 1, 0, outlineColor);
	DrawLine( x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine( x + 1, i, l - 2, 1, 0, fillColor);
};



void Game::CheckInput() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
			if (event.key.keysym.sym == SDLK_n) quit = 2;
			if (event.key.keysym.sym == SDLK_UP) player.VelY = -1;
			if (event.key.keysym.sym == SDLK_DOWN) player.VelY = 1;
			if (event.key.keysym.sym == SDLK_LEFT) {
				player.VelX = -1;
				player.direction = 1;
			} 
			if (event.key.keysym.sym == SDLK_RIGHT) {
				player.VelX = 1;
				player.direction = 0;
			}
			if (event.key.keysym.sym == SDLK_w) player.shootBullet(0,-1);
			if (event.key.keysym.sym == SDLK_s) player.shootBullet(0, 1);
			if (event.key.keysym.sym == SDLK_a) player.shootBullet(-1, 0);
			if (event.key.keysym.sym == SDLK_d) player.shootBullet(1, 0);

			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_UP && player.VelY < 0) player.VelY = 0;
			if (event.key.keysym.sym == SDLK_DOWN && player.VelY > 0) player.VelY = 0;
			if (event.key.keysym.sym == SDLK_LEFT && player.VelX < 0) player.VelX = 0;
			if (event.key.keysym.sym == SDLK_RIGHT && player.VelX > 0) player.VelX = 0;
			break;
		case SDL_QUIT:
			quit = 1;
			break;
		};
	};
}

void Game::displayInterface() {
	// tekst informacyjny / info text
	DrawRectangle(SCREEN_WIDTH - 120 , 0, 120, 35, czerwony, czarny);
	//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
	sprintf(text, "Time: %.1lfs", worldTime);
	DrawString(SCREEN_WIDTH-10 -2* strlen(text) * 8 / 2, 5, text);

	//When player can Shoot TETETE
	DrawRectangle(0, 0, 120, 35, czerwony, czarny);
	sprintf(text, "Boss HP: %d", boss.health);
	DrawString(5, 5, text);
	sprintf(text, "Player HP: %d", player.health);
	DrawString(5, 15, text);


	sprintf(text, "  %.0lf FPS", fps);
	DrawString(SCREEN_WIDTH-10 - 2 * strlen(text) * 8 / 2, 20, text);
	//	      "Esc - exit, \030 - faster, \031 - slower"

	DrawRectangle(5, SCREEN_HEIGHT - 25, 250, 20, czerwony, czarny);

	sprintf(text, "Esc - quit, \030 \031 \032 \033 - movement");
	DrawString(10, SCREEN_HEIGHT-20, text);
}

bool Game::UpdateTime() {

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;
	distance = 0;
	etiSpeed = 1;
	

	//SDL_Surface* background = SDL_LoadBMP("./background.bmp");
	while (!quit) {
		t2 = SDL_GetTicks();
		

		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna³ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		// here t2-t1 is the time in milliseconds since
		// the last screen was drawn
		// delta is the same time in seconds
		delta = (t2 - t1) * 0.001;
		t1 = t2;
		player.lastShoot += delta;
		boss.lastShoot += delta;
		worldTime += delta;

		distance += boss.bossSpeed * delta;

		SDL_FillRect(screen, NULL, czarny);
		DrawSurface(background, LEVEL_WIDTH / 2 + player.offsetX, LEVEL_HEIGHT / 2 + player.offsetY);
		//DrawSurface(background, SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 );

		player.movePlayer(delta);
		displayHP(player.positionX, player.positionY, player.health,player.maxHelath, boss.positionX, boss.positionY, boss.health,boss.maxHealth,boss.BOSS_WIDTH,boss.BOSS_HEIGHT, player.offsetX, player.offsetY);
		for (int o = 0; o < 100; o++) {
			player.bullets[o].calcBullet();
			if (player.bullets[o].alive) {
				DrawSurface(player.bulletSprite, player.bullets[o].positionX + player.offsetX, player.bullets[o].positionY + player.offsetY);
				if (player.bullets[o].checkCollision(boss.positionX, boss.positionY, boss.bWidth, boss.bHeight))
				{
					boss.health--;
					player.bullets[o].alive = false;
				}
			}
		}

		for (int o = 0; o <200; o++) {
			boss.bullets[o].calcBullet();
			if (boss.bullets[o].alive) {
				DrawSurface(boss.bulletSprite, boss.bullets[o].positionX + player.offsetX, boss.bullets[o].positionY + player.offsetY);
				if (boss.bullets[o].checkCollision(player.positionX, player.positionY, player.pWidth, player.pHeight))
				{
					player.hitPlayer();
					
					boss.bullets[o].alive = false;
				}
			}
		}
		player.keepSafe(delta);

		DrawSurface(player.sprite, player.positionX + player.offsetX, player.positionY + player.offsetY);
		if (boss.canMove) {
			boss.moveBoss(delta, distance);
		}
		
			DrawSurface(boss.sprite, boss.positionX + player.offsetX, boss.positionY + player.offsetY);
		
		boss.startAttack(worldTime);
		//DrawSurface(eti, player.positionX, player.positionY);
		//DrawSurface(eti,player.positionX, player.positionY);

		fpsTimer += delta;
		if (fpsTimer > 0.5) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
		};

		displayInterface();

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);


		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		checkGameStatus();
		CheckInput();
		frames++;
	};
	//esc - 1
	// n - 2
	if (player.health <= 0) {
		displayDefeat();
		QuitGame();
		return false;
	}
	if (boss.health <= 0) {
		displayVictory();
		QuitGame();
		return false;
	}

	QuitGame();
	if (quit == 1) {
		actualLevel = 0;
		return false;
	}
	else if(quit==2) {
		return false;
	}
}

void Game::displayMenu() {
	SDL_FillRect(screen, NULL, czarny);
	DrawSurface(menu, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//		SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Game::displayHP(double pX, double pY, int pHealth,int pMaxHealth, double bX, double bY, int bHealth, int bMaxHealth,int bWidth,int bHeight,double offsetX, double offsetY) {
	double pMinus = 0, bMinus = 0;
	if (pHealth == pMaxHealth) { pMinus = 1; }
	else {
		pMinus = double(double( pHealth)/ double( pMaxHealth) );
	}
	if (bHealth == bMaxHealth) { bMinus = 1; }
	else {
		bMinus = double(double(bHealth) / double(bMaxHealth));
	}

	if (pMinus < 0) {
		pMinus = 0;
	}
	if (bMinus < 0) {
		bMinus = 0;
	}

	if (!(pX - (PLAYER_WIDTH)+offsetX<0 || pX - (PLAYER_WIDTH)+offsetX + 1 > SCREEN_WIDTH || pY - PLAYER_WIDTH + offsetY < 0)) {
		DrawRectangle(pX - (PLAYER_WIDTH)+offsetX, pY - PLAYER_WIDTH + offsetY, 2 * PLAYER_WIDTH, 15, czarny, czarny);
		DrawRectangle(pX - (PLAYER_WIDTH)+offsetX + 1, pY - PLAYER_WIDTH + offsetY + 1, (2 * PLAYER_WIDTH - 2) * pMinus, 13, czarny, czerwony);
	}
	
	double shorterConditionX = bX - (bWidth / 2) + offsetX + 1 + bWidth;
	double shorterConditionY = bY - bWidth / 2 + offsetY+15;
	if(!((bX - (bWidth / 2) + offsetX) < 0 || (bX - (bWidth / 2) + offsetX) > SCREEN_WIDTH || shorterConditionX <0 || shorterConditionX > SCREEN_WIDTH ||shorterConditionY<0|| shorterConditionY>SCREEN_HEIGHT)) {
		DrawRectangle(bX - (bWidth/2)+offsetX, bY - bWidth/2 + offsetY,  bWidth, 15, czarny, czarny);
		DrawRectangle(bX - (bWidth/2)+offsetX + 1, bY - bWidth/2 + offsetY + 1, ( bWidth - 2) * bMinus, 13, czarny, czerwony);
	}
	
}

void Game::displayVictory() {
	DrawSurface(victory, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 );



	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//		SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);

	bool closeWhile = false;
	while (!closeWhile) {
		while (SDL_WaitEvent(&event)) {
			if (closeWhile) {
				break;
			}
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_RETURN:
					actualLevel = (actualLevel+1)%4;
					closeWhile = true;
					break;
				case SDLK_ESCAPE:
					actualLevel = 0;
					closeWhile = true;
					break;
				}
			}
		}
	}
}


void Game::displayDefeat() {
	DrawSurface(defeat, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);



	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//		SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);

	bool closeWhile = false;
	while (!closeWhile) {
		while (SDL_WaitEvent(&event)) {
			if (closeWhile) {
				break;
			}
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_RETURN:
					closeWhile = true;
					break;
				case SDLK_ESCAPE:
					actualLevel = 0;
					closeWhile = true;
					break;
				}
			}
		}
	}
}

void Game::checkGameStatus() {
	if (player.health <= 0 || boss.health <= 0) {
		quit = 2;
	}
}

void Game::pickLevel() {
	displayMenu();
	if (actualLevel == 0) {
		bool closeWhile = false;
		while (!closeWhile) {
			while (SDL_WaitEvent(&event)) {
				if (closeWhile) {
					break;
				}
				if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_1:
						actualLevel = 1;
						closeWhile = true;
						break;
					case SDLK_2:
						actualLevel = 2;
						closeWhile = true;
						break;
					case SDLK_3:
						actualLevel = 3;
						closeWhile = true;
						break;
					case SDLK_ESCAPE:
						QuitGame();
						exit(0);
						break;
					}
				}
			}
		}
	}
}

void Game::setLevel() {
	boss.type = actualLevel;
	switch (actualLevel)
	{
	case 1:
		boss.bulletSpeed = 0.7;
		boss.positionX = LEVEL_WIDTH / 2 + 150;
		boss.positionY = LEVEL_HEIGHT / 2;
		boss.sprite = LoadImage("./images/boss1.bmp");
		boss.bWidth = 200;
		boss.bHeight = 173;
		boss.maxHealth = 20;
		boss.health = boss.maxHealth;
		background = LoadImage("./images/background.bmp");
		player.positionX = SCREEN_WIDTH / 2 - 200;
		player.positionY = LEVEL_HEIGHT / 2;
		break;
	case 2:
		boss.bulletSpeed = 0.8;
		boss.shootCooldown = 0.2;
		boss.positionX = LEVEL_WIDTH / 2 + 20;
		boss.positionY = LEVEL_HEIGHT / 2 + 150;
		boss.sprite = LoadImage("./images/boss2.bmp");
		boss.bWidth = 112;
		boss.bHeight = 152;
		boss.maxHealth = 40;
		boss.health = boss.maxHealth;
		background = LoadImage("./images/background2.bmp");
		player.positionX = SCREEN_WIDTH / 2 - 200;
		player.positionY = LEVEL_HEIGHT / 2 + 150;
		break;
	case 3:
		boss.bulletSpeed = 0.6;
		boss.shootCooldown = 0.1;
		boss.positionX = LEVEL_WIDTH / 2 + 20;
		boss.positionY = LEVEL_HEIGHT / 2 ;
		boss.sprite = LoadImage("./images/boss3.bmp");
		boss.bWidth = 176;
		boss.bHeight = 123;
		boss.canMove = true;
		boss.maxHealth = 60;
		boss.health = boss.maxHealth;
		background = LoadImage("./images/background3.bmp");
		player.positionX = SCREEN_WIDTH / 2 - 100;
		player.positionY = LEVEL_HEIGHT / 2 + 400;
		break;
	}
}

void Game::QuitGame() {

	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(background);
	SDL_FreeSurface(menu);
	//player
	SDL_FreeSurface(player.heroL);
	SDL_FreeSurface(player.heroR);
	SDL_FreeSurface(player.heroLS);
	SDL_FreeSurface(player.heroRS);
	SDL_FreeSurface(player.bulletSprite);
	//boss
	SDL_FreeSurface(boss.sprite);
	SDL_FreeSurface(boss.bulletSprite);


	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}