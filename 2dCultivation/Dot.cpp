#include "Dot.h"
#include <iostream>
Dot::Dot()
{
	//Initialize the collision box
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;
	testBox.w = DOT_WIDTH;
	testBox.h = DOT_HEIGHT;
	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Dot::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY -= DOT_VEL; break;
		case SDLK_DOWN: mVelY += DOT_VEL; break;
		case SDLK_LEFT: mVelX -= DOT_VEL; break;
		case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += DOT_VEL; break;
		case SDLK_DOWN: mVelY -= DOT_VEL; break;
		case SDLK_LEFT: mVelX += DOT_VEL; break;
		case SDLK_RIGHT: mVelX -= DOT_VEL; break;
		}
	}
}

void Dot::move(Map* map, float timeStep)
{
	testBox.y = mBox.y;
	testBox.x = mBox.x;

	testBox.x += mVelX * timeStep;
	testBox.y += mVelY * timeStep;

	bool moveY = true;
	bool moveX = true;

	if ((testBox.x < 0) || (testBox.x + DOT_WIDTH > LEVEL_WIDTH))
	{
		moveX = false;
	}
	if ((testBox.y < 0) || (testBox.y + DOT_HEIGHT > LEVEL_HEIGHT))
	{
		moveY = false;
	}
	if (touchesWall(testBox, map)) {
		if (mVelX != 0)
			moveX = false;
		if (mVelY != 0)
			moveY = false;
	}
	if (moveY)
		mBox.y = testBox.y;

	if (moveX)
		mBox.x = testBox.x;

}

void Dot::setCamera(SDL_Rect& camera)
{
	//Center the camera over the dot
	camera.x = (mBox.x + DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (mBox.y + DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
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
	//Show the dot
	gDotTexture.render(mBox.x - camera.x, mBox.y - camera.y, gRenderer);
}

bool Dot::touchesWall(SDL_Rect box, Map* map)
{
	bool checkForWalls = true;
	if (checkForWalls) {

		if (map->checkTerrain(box)) {
			return true;
		}

	}

	//If no wall tiles were touched
	return false;
}

bool Dot::checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
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

	//If none of the sides from A are outside B
	return true;
}
