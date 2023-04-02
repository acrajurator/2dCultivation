#pragma once
#include <SDL_rect.h>
#include <iostream>
#include "Defs.h"
#include "Direction.h"
class Camera
{
public:
	void setCamera(float timeStep);

	SDL_Rect& getCamera();

	void setDirection(int x, int y);

private:

	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	Direction direction1 = Direction::none;
	Direction direction2 = Direction::none;
};

