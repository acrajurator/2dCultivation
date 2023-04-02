#include "Camera.h"


void Camera::setCamera(float timeStep)
{
	/*
		camera.x = (mBox.x + DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
		camera.y = (mBox.y + DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;*/

	if (direction1 == Direction::left)
		camera.x  -= CAMERA_VEL * timeStep;
	else if (direction1 == Direction::right)
		camera.x += CAMERA_VEL * timeStep; 
	if (direction2 == Direction::up)
		camera.y -= CAMERA_VEL * timeStep;
	else if (direction2 == Direction::down)
		camera.y += CAMERA_VEL * timeStep;


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

SDL_Rect& Camera::getCamera()
{
	return camera;
}

void Camera::setDirection(int x, int y)
{

	if (x < 50)
		direction1 = Direction::left;
	else if (x >   SCREEN_WIDTH - 50)
		direction1 = Direction::right;
	else 
		direction1 = Direction::none;
	if (y < 50)
		direction2 = Direction::up;
	else if (y > SCREEN_HEIGHT - 50)
		direction2 = Direction::down;
	else
		direction2 = Direction::none;
}
