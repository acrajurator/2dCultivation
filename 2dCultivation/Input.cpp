#include "Input.h"
#include <iostream>
#include "Camera.h"


void Input::handleEvent(SDL_Event& e, Dot& dot, Map& map, Camera& camera, AI& ai)
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
			
			int x, y;

			SDL_GetMouseState(&x, &y);
			x += camera.getCamera().x;
			y += camera.getCamera().y;
			Tile* dest;
			try {
				dest = &map.getTileClick(x, y);
				std::cout << dest->getType();
				dot.setPath(ai.aStar(*dest, dot.getCurrentTile()));
				
			}
			catch (int x) {
				std::cerr << "We caught an int exception with value: " << x << '\n';
			}
			//
			dest = nullptr;
		}
		if (e.type == SDL_MOUSEMOTION) {

			int x, y;

			SDL_GetMouseState(&x, &y);

			camera.setDirection(x, y);

		}

	
}
