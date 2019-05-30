#ifndef BOARD_H
#define BOARD_H

#include "pawn.h"
#include <memory>

#include <SFML/Graphics.hpp>

enum MoveType{
	INVALID,
	NORMAL,
	BEAT,
};

class Board{
public:
	std::shared_ptr<Pawn> field[8][8]= {nullptr};
	std::shared_ptr<Pawn> getPawn(sf::Vector2i& coords);
	MoveType checkMove(std::shared_ptr<Pawn> pawn, sf::Vector2i& start, sf::Vector2i& finish);
};
#endif