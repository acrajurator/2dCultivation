#pragma once
#include <SDL_image.h>

#include "Defs.h"
#include "LTexture.h"

//The tile
class Tile
{
public:
	//Initializes position and type
	Tile(int x, int y, int tileType, SDL_Rect clip);


	//Shows the tile
	void render(SDL_Rect& camera, LTexture& gTileTexture, SDL_Renderer& gRenderer);

	//Get the tile type
	int getType();

	//Get the collision box
	SDL_Rect getBox();

	//Box collision detector
	bool checkCollision(SDL_Rect a);
	//Box collision detector
	int checkCollisionDirection(SDL_Rect a);

private:
	//The attributes of the tile
	SDL_Rect mBox;

	//texturesheet part
	SDL_Rect textureClip;

	//The tile type
	int mType;
};