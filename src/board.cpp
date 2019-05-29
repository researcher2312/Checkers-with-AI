#include "board.h"

Pawn* Board::getPawn(sf::Vector2i& coords){
	if (field[coords.x-1][coords.y-1] != nullptr)
		return field[coords.x-1][coords.y-1];
	else
		return nullptr;
}

bool Board::moveIsValid(sf::Vector2i& start, sf::Vector2i& finish){
	if (finish.y == start.y + 1){
		if (finish.x == start.x + 1 || finish.x == start.x - 1){
			if (!getPawn(finish)){
				return true;
			}
		}
	}
	return false;
}