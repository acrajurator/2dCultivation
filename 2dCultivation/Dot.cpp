#include "Dot.h"
#include <iostream>
Dot::Dot()
{
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;
	direction = Direction::none;
	currentTile = NULL;
	startLocation = 0;
	viewDistance = 1;
	moving = false;
}

Dot::~Dot()
{
	currentTile = NULL;
}



void Dot::move(Map* map, float timeStep)
{
	if (!moving && !path.empty()) {
		moveDirection(path.top());
		path.pop();
		moving = true;
		
	}
	else {
	if (direction == Direction::up) {
		mBox.y -= DOT_VEL * timeStep;
		if (mBox.y < startLocation - TILE_HEIGHT) {
			setTile(currentTile->getNeighbour(Direction::up));
		}
	}
	else if (direction == Direction::left) {
		mBox.x -= DOT_VEL * timeStep;
		if (mBox.x < startLocation - TILE_WIDTH) {
			setTile(currentTile->getNeighbour(Direction::left));
		}
	}
	else if (direction == Direction::down) {
		mBox.y += DOT_VEL * timeStep;
		if (mBox.y > startLocation + TILE_HEIGHT) {
			setTile(currentTile->getNeighbour(Direction::down));
		}

	}
	else if (direction == Direction::right) {
		mBox.x += DOT_VEL * timeStep;
		if (mBox.x > startLocation + TILE_WIDTH) {
			setTile(currentTile->getNeighbour(Direction::right));
		}
	}
	}
}

void Dot::setCamera(SDL_Rect& camera)
{
	camera.x = (mBox.x + DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (mBox.y + DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void Dot::render(SDL_Rect& camera, LTexture& gDotTexture, SDL_Renderer& gRenderer)
{
	gDotTexture.render(mBox.x - camera.x, mBox.y - camera.y, gRenderer);
}


bool Dot::checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

void Dot::setTile(Tile& tile)
{
		SDL_Rect tileBox = tile.getBox();
		currentTile = &tile;

		mBox.y = tileBox.y+(TILE_WIDTH/2);
		mBox.x = tileBox.x+(TILE_HEIGHT/2);
		direction = Direction::none;
		moving = false;
	
		updateKnownTiles();
		printKnownTilesTypes();

}

void Dot::moveDirection(Direction desiredDirection)
{
	if (currentTile->validNeighbour(desiredDirection))
	{
		if (desiredDirection == Direction::up || desiredDirection == Direction::down) {
			startLocation = mBox.y;
		}
		else {
			startLocation = mBox.x;

		}
		direction = desiredDirection;
	}

}

void Dot::updateKnownTiles()
{
	int distanceUp{ 0 };
	int distanceDown{ 0 };

	knownTiles.clear();
	Tile* testTile = currentTile;
	Tile* testTileUp = currentTile;
	Tile* testTileDown = currentTile;
		for (int x = 0; x < viewDistance; ++x) {
			if (testTile->validNeighbour(Direction::up)) {
				testTile = &testTile->getNeighbour((Direction::up));
				knownTiles.push_back(testTile);
				distanceUp += 1;
			}
		}
		testTile = currentTile;
		for (int x = 0; x < viewDistance; ++x) {
			if (testTile->validNeighbour(Direction::down)) {
				testTile = &testTile->getNeighbour((Direction::down));
				knownTiles.push_back(testTile);
				distanceDown += 1;
			}
		}

		testTile = currentTile;
		for (int x = 0; x < viewDistance; ++x) {
			if (testTile->validNeighbour(Direction::left)) {
				testTile = &testTile->getNeighbour((Direction::left));
				knownTiles.push_back(testTile);
				testTileUp = testTile;
				for (int i = 0; i < distanceUp; ++i) {
					testTileUp = &testTileUp->getNeighbour((Direction::up));
					knownTiles.push_back(testTileUp);
				}
				testTileDown = testTile;
				for (int i = 0; i < distanceDown; ++i) {
					testTileDown = &testTileDown->getNeighbour((Direction::down));
					knownTiles.push_back(testTileDown);
				}

			}
		}

		testTile = currentTile;
		for (int x = 0; x < viewDistance; ++x) {
			if (testTile->validNeighbour(Direction::right)) {
				testTile = &testTile->getNeighbour((Direction::right));
				knownTiles.push_back(testTile);

				testTileUp = testTile;
				for (int i = 0; i < distanceUp; ++i) {
					testTileUp = &testTileUp->getNeighbour((Direction::up));
					knownTiles.push_back(testTileUp);
				}
				testTileDown = testTile;
				for (int i = 0; i < distanceDown; ++i) {
					testTileDown = &testTileDown->getNeighbour((Direction::down));
					knownTiles.push_back(testTileDown);
				}
			}
		}
		testTile = nullptr;
		testTileUp = nullptr;
		testTileDown = nullptr;

		
}

void Dot::printKnownTilesTypes()
{
	for (int x = 0; x < knownTiles.size(); ++x) {
		std::cout << "TileType: " << knownTiles[x]->getType() << "\n";
	}
	std::cout << "-----------------------------: \n";
}

Direction Dot::getDirection()
{
	return direction;
}

void Dot::pickupBonus()
{
	currentTile->pickupBonus();
}

Tile& Dot::getCurrentTile()
{
	return *currentTile;
}

void Dot::setPath(std::stack<Direction> aStar)
{
	path = aStar;
}
