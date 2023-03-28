#pragma once
#include <SDL_image.h>

#include "Defs.h"
#include "LTexture.h"
#include "Direction.h"


class Tile
{
public:

	Tile();

	~Tile();

	Tile(int x, int y, int tileType, SDL_Rect clip);

	void render(SDL_Rect& camera, LTexture& gTileTexture, SDL_Renderer& gRenderer);

	int getType();

	SDL_Rect getBox();

	bool checkCollision(SDL_Rect a);

	int checkCollisionDirection(SDL_Rect a);

	Tile& getNeighbour(Direction direction);

	bool validNeighbour(Direction direction);

	void setNeighbour(Tile& tile, Direction direction);


private:
	SDL_Rect mBox;

	SDL_Rect textureClip;

	Tile* tiles[4];



	int mType;

};