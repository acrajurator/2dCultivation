#pragma once
#include <SDL.h>
#include "Tile.h"
#include "Defs.h"
#include <random>

class Map
{
public:
	Map();

	~Map();

	bool generateMap(SDL_Rect* rect);

	void closeMap();

	bool checkTerrain(SDL_Rect a);

	void render(SDL_Rect& camera, LTexture& gTileTexture, SDL_Renderer& gRenderer, LTexture& gDotTexture, LTexture& gDotRedTexture, LTexture& gDotGreyTexture, LTexture& gDotPurpleTexture);

	Tile& getTile(int x, int y);

	Tile& getTileClick(int x, int y);

private:

	Tile worldMap[TILE_ROW][TILE_COL];
};


