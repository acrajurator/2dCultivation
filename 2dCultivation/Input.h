#pragma once
#include <SDL.h>
#include "Dot.h"
#include "Direction.h"
class Input
{
public:

	void handleEvent(SDL_Event& e, Dot& dot, Map& map);

};

