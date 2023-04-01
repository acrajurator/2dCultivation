#pragma once
#include <SDL_image.h>
#include "Tile.h"
#include "LTexture.h"
#include "Defs.h"
#include "Map.h"
#include "Direction.h"
#include <vector>
#include <stack>
#include "AI.h"

class Dot
{
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	static const int DOT_VEL = 222;

	Dot(AI& ai);

	~Dot();


	void move(Map* map, float timeStep);

	void setCamera(SDL_Rect& camera);

	void render(SDL_Rect& camera, LTexture& gDotTexture, SDL_Renderer& gRenderer);

	bool checkCollision(SDL_Rect a);

	void setTile(Tile& tile);

	void moveDirection(Direction desiredDirection);

	void updateKnownTiles();

	void printKnownTilesTypes();

	Direction getDirection();

	void pickupBonus();

	Tile& getCurrentTile();

	void setPath(std::stack<Direction> aStar);

	void decisionMaking();

	void lookForJob();

	void pickUpCoin();


private:
	AI* ai;
	SDL_Rect mBox;
	bool moving;
	bool busy;
	Direction direction;
	JobTypes currentJob;
	Tile* currentTile;
	int startLocation;
	int viewDistance;
	std::stack<Direction> path;
	std::vector<Tile*> knownTiles;
};