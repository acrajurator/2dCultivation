#pragma once
#include <SDL_image.h>
#include "Tile.h"
#include "LTexture.h"
#include "Defs.h"
//The dot that will move around on the screen
class Dot
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 10;

	//Initializes the variables
	Dot();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot and check collision against tiles
	void move(Tile* tiles[]);

	//Centers the camera over the dot
	void setCamera(SDL_Rect& camera);

	//Shows the dot on the screen
	void render(SDL_Rect& camera, LTexture& gDotTexture, SDL_Renderer& gRenderer);

	//Checks collision box against set of tiles
	bool touchesWall(SDL_Rect box, Tile* tiles[]);

	//Box collision detector
	bool checkCollision(SDL_Rect a, SDL_Rect b);

private:
	//Collision box of the dot
	SDL_Rect mBox;

	//The velocity of the dot
	int mVelX, mVelY;
};