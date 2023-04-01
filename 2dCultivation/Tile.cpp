#include "Tile.h"
#include <iostream>

Tile::Tile()
{
}

Tile::~Tile()
{
	for (int i = 0; i < 4; ++i)
	{
		tiles[i] = NULL;
	}
}

Tile::Tile(int x, int y, int tileType, SDL_Rect clip)
{
	mBox.x = x;
	mBox.y = y;

	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	mType = tileType;
	textureClip = clip;
	
	for (int i = 0; i < 4; ++i)
	{
		tiles[i] = nullptr;
	}
	collectTarget = true;
	killTarget = true;
	exploreTarget = true;
	patrolTarget = true;
}
void Tile::render(SDL_Rect& camera, LTexture& gTileTexture, SDL_Renderer& gRenderer, LTexture& gDotTexture, LTexture& gDotRedTexture, LTexture& gDotGreyTexture, LTexture& gDotPurpleTexture)
{
	if (checkCollision(camera))
	{
		gTileTexture.render(mBox.x - camera.x, mBox.y - camera.y, gRenderer, &textureClip);
		if (collectTarget)
			gDotTexture.render(mBox.x - camera.x, mBox.y - camera.y, gRenderer);
		if (killTarget)
			gDotRedTexture.render(mBox.x + TILE_WIDTH - 20 - camera.x, mBox.y + TILE_HEIGHT - 20 - camera.y, gRenderer);
		if (exploreTarget)
			gDotGreyTexture.render(mBox.x - camera.x, mBox.y+TILE_HEIGHT-20 - camera.y, gRenderer);
		if (patrolTarget)
			gDotPurpleTexture.render(mBox.x+TILE_WIDTH-20 - camera.x, mBox.y - camera.y, gRenderer);
	}
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}

bool Tile::checkCollision(SDL_Rect a)
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
	if (a.w == 1)
	std::cout << "Collision with: " << getType() << " \n";
	return true;
}

int Tile::checkCollisionDirection(SDL_Rect a)
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

	int numbers[4]{ abs(topA - bottomB), abs(bottomA - topB), abs(leftA - rightB), abs(rightA - leftB) };
	int smallest{100};
	int smallestIndex{-1};
	for (int i = 0; i < 4; ++i)
	{
		if (numbers[i] < smallest)
		{
			smallest = numbers[i];
			smallestIndex = i;
		}
	}

	return smallestIndex;
}

Tile& Tile::getNeighbour(Direction direction)
{


	if (direction == Direction::up) {

		return *tiles[0];
	}
	else if (direction == Direction::down) {
		return *tiles[1];
	}
	else if (direction == Direction::left) {
		return *tiles[2];
	}
	else if (direction == Direction::right) {
		return *tiles[3];
	}
}

bool Tile::validNeighbour(Direction direction)
{
	if (direction == Direction::up) {
		if (tiles[0] != nullptr)
			return true;
	}
	else if (direction == Direction::down) {
		if (tiles[1] != nullptr)
			return true;
	}
	else if (direction == Direction::left) {
		if (tiles[2] != nullptr)
			return true;
	}
	else if (direction == Direction::right) {
		if (tiles[3] != nullptr)
			return true;
	}
	return false;
}

void Tile::setNeighbour(Tile& tile, Direction direction)
{
	if (direction == Direction::up) {
		tiles[0] = &tile;
	}
	else if (direction == Direction::down) {
		tiles[1] = &tile;
	}
	else if (direction == Direction::left) {
		tiles[2] = &tile;
	}
	else if (direction == Direction::right) {
		tiles[3] = &tile;
	}
}

void Tile::pickup(JobTypes type)
{

	if (type == JobTypes::collect)
		collectTarget = false;

	if (type == JobTypes::kill)
	 killTarget = false;

	if (type == JobTypes::explore)
	 exploreTarget = false;

	if (type == JobTypes::patrol)
	 patrolTarget = false;
}

bool Tile::getBonus(JobTypes type)
{
	if (type == JobTypes::collect)
		return collectTarget;

	if (type == JobTypes::kill)
		return killTarget;

	if (type == JobTypes::explore)
		return exploreTarget;

	if (type == JobTypes::patrol)
		return patrolTarget;
}

void Tile::setGCost(double gCostNew)
{
	gCost = gCostNew;
}

void Tile::setHCost(double hCostNew)
{
	hCost = hCostNew;
}

void Tile::setFCost(double fCostNew)
{
	fCost = fCostNew;
}

double Tile::getGCost()
{
	return gCost;
}

double Tile::getHCost()
{
	return hCost;
}

double Tile::getFCost()
{
	return fCost;
}


bool Tile::compareFCost(Tile* a, Tile* b)
{

	return a->getFCost() > b->getFCost();
}

void Tile::setPath(Direction pathAI)
{
	path = pathAI;
}

Direction Tile::getPath()
{
	return path;
}

