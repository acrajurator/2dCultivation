#pragma once
#include <SDL_image.h>

#include "Defs.h"
#include "LTexture.h"
#include "Direction.h"
#include "JobTypes.h"



class Tile
{
public:

	Tile();

	~Tile();

	Tile(int x, int y, int tileType, SDL_Rect clip);

	void render(SDL_Rect& camera, LTexture& gTileTexture, SDL_Renderer& gRenderer, LTexture& gDotTexture, LTexture& gDotRedTexture, LTexture& gDotGreyTexture, LTexture& gDotPurpleTexture);

	int getType();

	SDL_Rect getBox();

	bool checkCollision(SDL_Rect a);

	int checkCollisionDirection(SDL_Rect a);

	Tile& getNeighbour(Direction direction);

	bool validNeighbour(Direction direction);

	void setNeighbour(Tile& tile, Direction direction);

	void pickup(JobTypes type);
	bool getBonus(JobTypes type);

	void setGCost(double gCost);
	void setHCost(double hCost);
	void setFCost(double fCost);
	double getGCost();
	double getHCost();
	double getFCost();
	static bool compareFCost(Tile* a, Tile* b);
	void setPath(Direction path);
	Direction getPath();


private:
	SDL_Rect mBox;

	SDL_Rect textureClip;

	Tile* tiles[4];

	Direction path;
	bool collectTarget;
	bool killTarget;
	bool exploreTarget;
	bool patrolTarget;

	int mType;
	double gCost;
	double hCost;
	double fCost;
};