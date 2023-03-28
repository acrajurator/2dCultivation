#pragma once
#include <SDL_image.h>
#include "Tile.h"
#include "LTexture.h"
#include "Defs.h"
#include "Map.h"
#include "Direction.h"
#include <vector>

class Dot
{
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	static const int DOT_VEL = 640;

	Dot();

	~Dot();

	void handleEvent(SDL_Event& e);

	void move(Map* map, float timeStep);

	void setCamera(SDL_Rect& camera);

	void render(SDL_Rect& camera, LTexture& gDotTexture, SDL_Renderer& gRenderer);

	bool touchesWall(SDL_Rect box, Map* map);

	bool checkCollision(SDL_Rect a, SDL_Rect b);

	void setTile(Tile& tile);

	void moveDirection(Direction desiredDirection);

	void updateKnownTiles();

	void printKnownTilesTypes();

private:
	SDL_Rect mBox;

	Direction direction;
	Tile* currentTile;
	int startLocation;
	int viewDistance;

	std::vector<Tile*> knownTiles;
};