#include "Input.h"


void Input::handleEvent(SDL_Event& e, Dot& dot, Map& map, SDL_Rect& camera)
{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && dot.getDirection() == Direction::none)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: dot.moveDirection(Direction::up);
				break;
			case SDLK_DOWN:  dot.moveDirection(Direction::down);
				break;
			case SDLK_LEFT:  dot.moveDirection(Direction::left);
				break;
			case SDLK_RIGHT:  dot.moveDirection(Direction::right);
				break;
			case SDLK_SPACE: dot.pickupBonus();
				break;
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			
			SDL_Rect mBox;
			mBox.w = 1;
			mBox.h = 1;
			int x, y;

			SDL_GetMouseState(&x, &y);
			mBox.x = x + camera.x;
			mBox.y = y + camera.y;
			map.checkTerrain(mBox);

		}

	
}
