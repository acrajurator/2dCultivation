#include "Dot.h"
#include <iostream>
Dot::Dot(AI& aiNew)
{
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;
	direction = Direction::none;
	currentJob = JobTypes::none;
	currentTile = NULL;
	startLocation = 0;
	viewDistance = 1;
	moving = false;
	busy = false;
	ai = &aiNew;
}

Dot::~Dot()
{
	currentTile = NULL;
	ai = nullptr;
}



void Dot::move(Map* map, float timeStep)
{
	if (!moving && !path.empty()) {
		moveDirection(path.top());
		path.pop();
		moving = true;
		std::cout << "moving\n";
		
	}
	if (!moving && busy) {
		std::cout << "Picking up coin\n";
		pickUpCoin();
	}
	else if(!busy && !moving) {
		std::cout << "Making decision\n";
		decisionMaking();
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

		std::cout << mBox.y << "\n";
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


void Dot::render(SDL_Rect& camera, LTexture& gDotTexture, SDL_Renderer& gRenderer)
{

	gDotTexture.render(mBox.x - camera.x, mBox.y - camera.y, gRenderer);
}
bool Dot::checkCollision(SDL_Rect a)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = mBox.x;
	rightB = mBox.x + mBox.w;
	topB = mBox.y;
	bottomB = mBox.y + mBox.h;

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
		//printKnownTilesTypes();

}

void Dot::moveDirection(Direction desiredDirection)
{
	if (currentTile->validNeighbour(desiredDirection))
	{
		if (desiredDirection == Direction::up || desiredDirection == Direction::down) {
			startLocation = mBox.y;

			std::cout << "start location y\n";
		}
		else {
			startLocation = mBox.x;

			std::cout << "start location x\n";
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
				if (FOGOFWAR)
					testTile->setFog(false);
				knownTiles.push_back(testTile);
				distanceUp += 1;
			}
		}
		testTile = currentTile;
		for (int x = 0; x < viewDistance; ++x) {
			if (testTile->validNeighbour(Direction::down)) {
				testTile = &testTile->getNeighbour((Direction::down));
				if (FOGOFWAR)
					testTile->setFog(false);
				knownTiles.push_back(testTile);
				distanceDown += 1;
			}
		}

		testTile = currentTile;
		for (int x = 0; x < viewDistance; ++x) {
			if (testTile->validNeighbour(Direction::left)) {
				testTile = &testTile->getNeighbour((Direction::left));
				if (FOGOFWAR)
					testTile->setFog(false);
				knownTiles.push_back(testTile);
				testTileUp = testTile;
				for (int i = 0; i < distanceUp; ++i) {
					testTileUp = &testTileUp->getNeighbour((Direction::up));
					if (FOGOFWAR)
						testTile->setFog(false);
					knownTiles.push_back(testTileUp);
				}
				testTileDown = testTile;
				for (int i = 0; i < distanceDown; ++i) {
					testTileDown = &testTileDown->getNeighbour((Direction::down));
					if (FOGOFWAR)
						testTile->setFog(false);
					knownTiles.push_back(testTileDown);
				}

			}
		}

		testTile = currentTile;
		for (int x = 0; x < viewDistance; ++x) {
			if (testTile->validNeighbour(Direction::right)) {
				testTile = &testTile->getNeighbour((Direction::right));
				if (FOGOFWAR)
					testTile->setFog(false);
				knownTiles.push_back(testTile);

				testTileUp = testTile;
				for (int i = 0; i < distanceUp; ++i) {
					testTileUp = &testTileUp->getNeighbour((Direction::up));
					if (FOGOFWAR)
						testTile->setFog(false);
					knownTiles.push_back(testTileUp);
				}
				testTileDown = testTile;
				for (int i = 0; i < distanceDown; ++i) {
					testTileDown = &testTileDown->getNeighbour((Direction::down));
					if (FOGOFWAR)
						testTile->setFog(false);
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
	currentTile->pickup(JobTypes::collect);
}

Tile& Dot::getCurrentTile()
{
	return *currentTile;
}

void Dot::setPath(std::stack<Direction> aStar)
{
	path = aStar;
}

void Dot::decisionMaking()
{

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> die11{ 0, 3 };
	int action = die11(mt);
	if (action == 0)
		currentJob = JobTypes::collect;
	else if (action ==1)
		currentJob = JobTypes::kill;
	else if (action == 2)
		currentJob = JobTypes::explore;
	else if (action == 3)
		currentJob = JobTypes::patrol;
	

	lookForJob();
}

void Dot::lookForJob()
{

	std::cout << "Looking for job \n";
	bool foundJob{ false };

	for (auto var : knownTiles) {
		if (var->getBonus(currentJob)) {
			foundJob = true;
			setPath(ai->aStar(*var, getCurrentTile()));
			busy = true;
			return;
		}
	}


	std::cout << "Doing rng \n";
	std::mt19937 mt{ std::random_device{}() };
	int amountOfTiles = knownTiles.size() - 1;
	std::uniform_int_distribution<> die11{ 0,amountOfTiles };

	int tileTarget = -1;
	tileTarget = die11(mt);
	setPath(ai->aStar(*knownTiles[tileTarget], getCurrentTile()));


}

void Dot::pickUpCoin()
{
	if (!moving && busy) {
		currentTile->pickup(currentJob);
		busy = false;
		currentJob = JobTypes::none;
	}
}
