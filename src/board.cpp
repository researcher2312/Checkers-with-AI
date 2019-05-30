#include "board.h"

Pawn* Board::getPawn(sf::Vector2i& coords){
	if (field[coords.x][coords.y] != nullptr)
		return field[coords.x][coords.y];
	else
		return nullptr;
}

MoveType Board::checkMove(Pawn* pawn, sf::Vector2i& start, sf::Vector2i& finish){
	int direction = 1;
	if (pawn->owner == computer)
		direction = -1;
	if (finish.y == start.y + direction){
		if (finish.x == start.x + 1 || finish.x == start.x - 1){
			if (!getPawn(finish)){
				return NORMAL;
			}
		}
	}
	if (finish.y == start.y + 2*direction){
		if (finish.x == start.x + 2 || finish.x == start.x - 2){
			if (!getPawn(finish)){
				sf::Vector2i beaten_pawn(start.x + (finish.x - start.x)/2, start.y + direction);
				if (getPawn(beaten_pawn)->owner == otherPlayer(pawn->owner)){
					return BEAT;
				}
			}
		}
	}
	return INVALID;
}