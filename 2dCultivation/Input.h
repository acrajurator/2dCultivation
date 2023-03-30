#pragma once
#include <SDL.h>
#include "Dot.h"
#include "Direction.h"
#include "AI.h"
class Input
{
public:

	void handleEvent(SDL_Event& e, Dot& dot, Map& map, SDL_Rect& camera, AI& ai);

};

