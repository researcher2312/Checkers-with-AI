#ifndef BOARD_H
#define BOARD_H

#include "pawn.h"

#include <SFML/Graphics.hpp>

class Board{
public:
	Pawn* field[8][8]= {nullptr};
	Pawn* getPawn(sf::Vector2i& coords);
	bool moveIsValid(sf::Vector2i& start, sf::Vector2i& finish);
};
#endif