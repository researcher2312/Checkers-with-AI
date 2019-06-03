#ifndef BOARD_H
#define BOARD_H

#include "pawn.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

enum MoveType{
	INVALID,
	NORMAL,
	BEAT,
	MULTI_BEAT,
};

struct Move{
	Move(sf::Vector2i start_, sf::Vector2i finish_, MoveType type_): start(start_), finish(finish_), type(type_){};
	sf::Vector2i start;
	sf::Vector2i finish;
	MoveType type;
};

class Board{
public:
	std::shared_ptr<Pawn> field[8][8]= {nullptr};
	std::shared_ptr<Pawn> getPawn(const sf::Vector2i& coords);
	int setPawn(const sf::Vector2i& coords, const std::shared_ptr<Pawn>& new_ptr);
	std::shared_ptr<Pawn> movePawn(sf::Vector2i start, sf::Vector2i finish, MoveType type);
	MoveType checkMove(sf::Vector2i& start, sf::Vector2i& finish);
	std::vector<Move>* getAvailibleMoves(OwningPlayer player, const std::vector<std::weak_ptr<Pawn>>& pawns);
	std::vector<Move>* getAvailibleMoves(OwningPlayer player, const std::weak_ptr<Pawn>& pawn);
	int getScore (OwningPlayer player, const std::vector<std::weak_ptr<Pawn>>& pawns)
};
#endif