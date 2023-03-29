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

	int x = 0, y = 0;

	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j) {
			int tileType = -1;
			tileType = die11(mt);

			worldMap[i][j] = Tile(x, y, tileType, rect[tileType]);

			x += TILE_WIDTH;

		}
		x = 0;
		y += TILE_HEIGHT;
	}
	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j) 
		{
			for (int k = 0; k < 4; ++k)
			{

				if (k == 0 && i > 0) {
					worldMap[i][j].setNeighbour(worldMap[i-1][j], Direction::up);

				}
				if (k == 1 && i < TILE_COL-1) {
					worldMap[i][j].setNeighbour(worldMap[i+1][j], Direction::down);
				}
				if (k == 2 && j > 0) {
					worldMap[i][j].setNeighbour(worldMap[i][j-1], Direction::left);

				}
				if (k == 3 && j < TILE_ROW-1) {
					worldMap[i][j].setNeighbour(worldMap[i][j+1], Direction::right);

				}
			}
		}
	}


	generateMap = true;
	return generateMap;
}

void Map::closeMap()
{
	//for (int i = 0; i < TILE_ROW; ++i)
	//{
	//	for (int j = 0; j < TILE_COL; ++j) {

	//	if (worldMap[i][j] != NULL)
	//	{
	//		//delete worldMap[i][j];
	//		worldMap[i][j] = NULL;
	//	}

	//	}
	//}
}

bool Map::checkTerrain(SDL_Rect a)
{

	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j) 
		{

			//if ((worldMap[i][j].getType() == TILE_CENTER))
			//if ((worldMap[i][j]->getType() >= TILE_CENTER) && (worldMap[i][j]->getType() <= TILE_TOPLEFT))
			//{
				if (worldMap[i][j].checkCollision(a))
				{

					//std::cout << "Collision: " << worldMap[i][j].checkCollisionDirection(a) << "\n"; 
					return true;
				}
			//}

		}
	}

	return false;
}

void Map::render(SDL_Rect& camera, LTexture& gTileTexture, SDL_Renderer& gRenderer, LTexture& gDotTexture)
{
	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j)
		{
			worldMap[i][j].render(camera, gTileTexture, gRenderer, gDotTexture);
		}
	}
}

Tile& Map::getTile(int x, int y)
{
	return worldMap[x][y];
}
