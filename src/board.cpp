#include "board.h"

Pawn* Board::getPawn(sf::Vector2i& coords){
	if (field[coords.x][coords.y] != nullptr)
		return field[coords.x][coords.y];
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