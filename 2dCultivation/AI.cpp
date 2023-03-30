#include "AI.h"
#include <iostream>



double AI::distance(Tile& a, Tile& b)
{
	int x1 = a.getBox().x;
	int y1 = a.getBox().y;
	int x2 = b.getBox().x;
	int y2 = b.getBox().y;
	// Calculating distance
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

std::vector<Direction> AI::aStar(Tile& player, Tile& dest) {
	std::vector<Direction> empty;


	//already at destination
	if (&player == &dest) {
		std::cout << "Already at location\n";
		return empty;
	}

	Tile* currentTile = &player;
	Tile* child;
	std::vector<Tile*> openList;
	std::vector<Tile*> closedList;
	openList.push_back(&player);
	bool destinationFound = false;

	while (!openList.empty()) {
		std::sort(openList.begin(), openList.end(), Tile::compareFCost);

		currentTile = std::move(openList.back());
		closedList.push_back(currentTile);
		openList.pop_back();

		if (currentTile == &dest) {
			std::cout << "Done Finding path\n";
			openList.empty();
			closedList.empty();
			currentTile = nullptr;
			child = nullptr;
			return empty;
		}


		if (currentTile->validNeighbour(Direction::up))
		{
			bool closer = true;
			child = &currentTile->getNeighbour(Direction::up);
			for (auto oldTile : closedList) {
				if (child == oldTile) {
					//no need to continue on this child
					closer = false;
					break;
				}
			}
			if (closer) {
				double gCostChild = currentTile->getGCost() + distance(*child, *currentTile);
				double hCostChild = distance(*child, dest);
				double fCostChild = gCostChild + hCostChild;
				for (auto oldTile : openList) {
					if (child == oldTile) {
						if (gCostChild > oldTile->getGCost()) {
							//go to next child
							closer = false;
							break;
						}
					}
				}
				if (closer) {
					child->setGCost(gCostChild);
					child->setHCost(hCostChild);
					child->setFCost(fCostChild);
					openList.push_back(child);
				}


			}

		}
		if (currentTile->validNeighbour(Direction::down))
		{
			bool closer = true;
			child = &currentTile->getNeighbour(Direction::down);
			for (auto oldTile : closedList) {
				if (child == oldTile) {
					//no need to continue on this child
					closer = false;
					break;
				}
			}
			if (closer) {
				double gCostChild = currentTile->getGCost() + distance(*child, *currentTile);
				double hCostChild = distance(*child, dest);
				double fCostChild = gCostChild + hCostChild;
				for (auto oldTile : openList) {
					if (child == oldTile) {
						if (gCostChild > oldTile->getGCost()) {
							//go to next child
							closer = false;
							break;
						}
					}
				}
				if (closer) {
					child->setGCost(gCostChild);
					child->setHCost(hCostChild);
					child->setFCost(fCostChild);
					openList.push_back(child);
				}


			}
		}
		if (currentTile->validNeighbour(Direction::left))
		{
			bool closer = true;
			child = &currentTile->getNeighbour(Direction::left);
			for (auto oldTile : closedList) {
				if (child == oldTile) {
					//no need to continue on this child
					closer = false;
					break;
				}
			}
			if (closer) {
				double gCostChild = currentTile->getGCost() + distance(*child, *currentTile);
				double hCostChild = distance(*child, dest);
				double fCostChild = gCostChild + hCostChild;
				for (auto oldTile : openList) {
					if (child == oldTile) {
						if (gCostChild > oldTile->getGCost()) {
							//go to next child
							closer = false;
							break;
						}
					}
				}
				if (closer) {
					child->setGCost(gCostChild);
					child->setHCost(hCostChild);
					child->setFCost(fCostChild);
					openList.push_back(child);
				}


			}
		}
		if (currentTile->validNeighbour(Direction::right))
		{
			bool closer = true;
			child = &currentTile->getNeighbour(Direction::right);
			for (auto oldTile : closedList) {
				if (child == oldTile) {
					//no need to continue on this child
					closer = false;
					break;
				}
			}
			if (closer) {
				double gCostChild = currentTile->getGCost() + distance(*child, *currentTile);
				double hCostChild = distance(*child, dest);
				double fCostChild = gCostChild + hCostChild;
				for (auto oldTile : openList) {
					if (child == oldTile) {
						if (gCostChild > oldTile->getGCost()) {
							//go to next child
							closer = false;
							break;
						}
					}
				}
				if (closer) {
					child->setGCost(gCostChild);
					child->setHCost(hCostChild);
					child->setFCost(fCostChild);
					openList.push_back(child);
				}


			}
		}


	}
}

