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

	void render(SDL_Rect& camera, LTexture& gTileTexture, SDL_Renderer& gRenderer, LTexture& gDotTexture);

	int getType();

	SDL_Rect getBox();

	bool checkCollision(SDL_Rect a);

	int checkCollisionDirection(SDL_Rect a);

	Tile& getNeighbour(Direction direction);

	bool validNeighbour(Direction direction);

	void setNeighbour(Tile& tile, Direction direction);

	void pickupBonus();

	void setGCost(double gCost);
	void setHCost(double hCost);
	void setFCost(double fCost);
	double getGCost();
	double getHCost();
	double getFCost();
	void setParent(Tile& parent);
	Tile& getParent();
	static bool compareFCost(Tile* a, Tile* b);
private:
	SDL_Rect mBox;

	SDL_Rect textureClip;

	Tile* tiles[4];


	bool bonus;

	int mType;
	double gCost;
	double hCost;
	double fCost;
	Tile* parent;
};