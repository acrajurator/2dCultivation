#include "Map.h"
#include <iostream>

Map::Map()
{
}

Map::~Map()
{
	closeMap();
}

bool Map::generateMap(SDL_Rect* rect)
{
	bool generateMap = false;
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> die11{ 0, 11 };

	//The tile offsets
	int x = 0, y = 0;

	//Determines what kind of tile will be made


	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j) {
			int tileType = -1;
			tileType = die11(mt);

			worldMap[i][j] = new Tile(x, y, tileType, rect[tileType]);

			//Move to next tile spot
			x += TILE_WIDTH;

		}
		//Move back
		x = 0;
		//Move to the next row
		y += TILE_HEIGHT;
	}
	generateMap = true;
	return generateMap;
}

void Map::closeMap()
{
	//Deallocate tiles
	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j) {

		if (worldMap[i][j] != NULL)
		{
			delete worldMap[i][j];
			worldMap[i][j] = NULL;
		}

		}
	}
}

bool Map::checkTerrain(SDL_Rect a)
{

	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j) 
		{

			//If the tile is a wall type tile
			if ((worldMap[i][j]->getType() == TILE_CENTER))
			//if ((worldMap[i][j]->getType() >= TILE_CENTER) && (worldMap[i][j]->getType() <= TILE_TOPLEFT))
			{
				//If the collision box touches the wall tile
				if (worldMap[i][j]->checkCollision(a))
				{

					std::cout << "Collision: " << worldMap[i][j]->checkCollisionDirection(a) << "\n"; 
					return true;
				}
			}

		}
	}

	return false;
}

void Map::render(SDL_Rect& camera, LTexture& gTileTexture, SDL_Renderer& gRenderer)
{
	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j)
		{
			worldMap[i][j]->render(camera, gTileTexture, gRenderer);
		}
	}
}
