#pragma once
#include "Map.h"

class AI
{
public:

    double distance(Tile& a, Tile& b);
    std::vector<Direction> aStar(Tile& player, Tile& dest);
private:


};

