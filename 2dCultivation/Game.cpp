
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "LTexture.h"
#include "Tile.h"
#include "Dot.h"
#include "Defs.h"
#include "Timer.h"
#include <iostream>
#include "Map.h"
#include "Input.h"
#include "AI.h"
#include "Camera.h"


bool init();

bool loadMedia();

void close();

bool setTiles();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gDotTexture;
LTexture gDotGreyTexture;
LTexture gDotRedTexture;
LTexture gDotPurpleTexture;
LTexture gTileTexture;
LTexture gSpaceTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
Map map;
Timer timer;
AI ai;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;
	if (!gSpaceTexture.loadFromFile("spacepic.jpg", *gRenderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	if (!gDotTexture.loadFromFile("dot.bmp", *gRenderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	if (!gDotGreyTexture.loadFromFile("dotgrey.bmp", *gRenderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	if (!gDotRedTexture.loadFromFile("dotred.bmp", *gRenderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	if (!gDotPurpleTexture.loadFromFile("dotpurple.bmp", *gRenderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	if (!gTileTexture.loadFromFile("tiles.png", *gRenderer))
	{
		printf("Failed to load tile set texture!\n");
		success = false;
	}

	if (!setTiles())
	{
		printf("Failed to load tile set!\n");
		success = false;
	}

	return success;
}

void close()
{
	 map.closeMap();
	 gSpaceTexture.free();
	gDotPurpleTexture.free();
	gDotRedTexture.free();
	gDotGreyTexture.free();
	gDotTexture.free();
	gDotTexture.free();
	gTileTexture.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}


bool setTiles()
{
			gTileClips[TILE_RED].x = 0;
			gTileClips[TILE_RED].y = 0;
			gTileClips[TILE_RED].w = TILE_WIDTH;
			gTileClips[TILE_RED].h = TILE_HEIGHT;

			gTileClips[TILE_GREEN].x = 0;
			gTileClips[TILE_GREEN].y = 80;
			gTileClips[TILE_GREEN].w = TILE_WIDTH;
			gTileClips[TILE_GREEN].h = TILE_HEIGHT;

			gTileClips[TILE_BLUE].x = 0;
			gTileClips[TILE_BLUE].y = 160;
			gTileClips[TILE_BLUE].w = TILE_WIDTH;
			gTileClips[TILE_BLUE].h = TILE_HEIGHT;

			gTileClips[TILE_TOPLEFT].x = 80;
			gTileClips[TILE_TOPLEFT].y = 0;
			gTileClips[TILE_TOPLEFT].w = TILE_WIDTH;
			gTileClips[TILE_TOPLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_LEFT].x = 80;
			gTileClips[TILE_LEFT].y = 80;
			gTileClips[TILE_LEFT].w = TILE_WIDTH;
			gTileClips[TILE_LEFT].h = TILE_HEIGHT;

			gTileClips[TILE_BOTTOMLEFT].x = 80;
			gTileClips[TILE_BOTTOMLEFT].y = 160;
			gTileClips[TILE_BOTTOMLEFT].w = TILE_WIDTH;
			gTileClips[TILE_BOTTOMLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_TOP].x = 160;
			gTileClips[TILE_TOP].y = 0;
			gTileClips[TILE_TOP].w = TILE_WIDTH;
			gTileClips[TILE_TOP].h = TILE_HEIGHT;

			gTileClips[TILE_CENTER].x = 160;
			gTileClips[TILE_CENTER].y = 80;
			gTileClips[TILE_CENTER].w = TILE_WIDTH;
			gTileClips[TILE_CENTER].h = TILE_HEIGHT;

			gTileClips[TILE_BOTTOM].x = 160;
			gTileClips[TILE_BOTTOM].y = 160;
			gTileClips[TILE_BOTTOM].w = TILE_WIDTH;
			gTileClips[TILE_BOTTOM].h = TILE_HEIGHT;

			gTileClips[TILE_TOPRIGHT].x = 240;
			gTileClips[TILE_TOPRIGHT].y = 0;
			gTileClips[TILE_TOPRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_TOPRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_RIGHT].x = 240;
			gTileClips[TILE_RIGHT].y = 80;
			gTileClips[TILE_RIGHT].w = TILE_WIDTH;
			gTileClips[TILE_RIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_BOTTOMRIGHT].x = 240;
			gTileClips[TILE_BOTTOMRIGHT].y = 160;
			gTileClips[TILE_BOTTOMRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_BOTTOMRIGHT].h = TILE_HEIGHT;
		
			if (!map.generateMap(gTileClips)) {
				printf("Failed to generate map!\n");
		}


	return true;
}



int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{

		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;

			SDL_Event e;
			Input input;
			Dot dot{ai};
			dot.setTile(map.getTile(10, 10));
			Camera camera{};

			int scrollingOffsetX = 0;
			SDL_RendererFlip flip = SDL_FLIP_NONE;
			SDL_RendererFlip flip2 = SDL_FLIP_HORIZONTAL;
			

			while (!quit)
			{

			//	std::cout << "Time taken: " << timer.getTicks() / 1000.f << " seconds\n";

				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					input.handleEvent(e,dot, map, camera, ai);
				}


				float timeStep = timer.getTicks() / 1000.f;
				dot.move(&map, timeStep);
				camera.setCamera(timeStep);

				//Scroll background
				--scrollingOffsetX;
				if (scrollingOffsetX < -gSpaceTexture.getWidth())
				{
					scrollingOffsetX = 0;
					if (flip == SDL_FLIP_NONE)
					{
						flip2 = (SDL_FLIP_NONE);
						flip = (SDL_FLIP_HORIZONTAL);
					}
					else if (flip == SDL_FLIP_HORIZONTAL)
					{
						flip2 = SDL_FLIP_HORIZONTAL;
						flip = SDL_FLIP_NONE;
					}
				}
				
				timer.start();


				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
				SDL_RenderClear(gRenderer);
				//scrolling background pic
				//gSpaceTexture.render(scrollingOffsetX, 0, *gRenderer, NULL, 0.0, NULL, flip2);
				//gSpaceTexture.render(scrollingOffsetX + gSpaceTexture.getWidth(), 0, *gRenderer, NULL, 0.0, NULL, flip);
				map.render(camera.getCamera(), gTileTexture, *gRenderer, gDotTexture, gDotRedTexture, gDotGreyTexture, gDotPurpleTexture);

				dot.render(camera.getCamera(), gDotTexture, *gRenderer);

				SDL_RenderPresent(gRenderer);

			}
		}

		close();
	}

	return 0;
}