#pragma once
#include "Map.h"
#include <stack>

class AI
{
public:

    double distance(Tile& a, Tile& b);
    std::stack<Direction> aStar(Tile& player, Tile& dest);
private:


};

