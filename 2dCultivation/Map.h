#pragma once
#include <SDL.h>
#include "Tile.h"
#include "Defs.h"
#include <random>

class Map
{
public:
	//Initializes position and type
	Map();

	~Map();

	bool generateMap(SDL_Rect* rect);

	void closeMap();

	bool checkTerrain(SDL_Rect a);

	void render(SDL_Rect& camera, LTexture& gTileTexture, SDL_Renderer& gRenderer);
private:

	Tile* worldMap[TILE_ROW][TILE_COL]{};
};


