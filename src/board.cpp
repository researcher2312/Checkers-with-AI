#include "board.h"
#include <iostream>

std::shared_ptr<Pawn> Board::getPawn(const sf::Vector2i& coords){
	if (field[coords.x][coords.y] != nullptr)
		return field[coords.x][coords.y];
	else
		return nullptr;
}

int Board::setPawn(const sf::Vector2i& coords, const std::shared_ptr<Pawn>& new_ptr){
	field[coords.x][coords.y] = new_ptr;
	return 0;
}

std::shared_ptr<Pawn> Board::movePawn(sf::Vector2i start, sf::Vector2i finish, MoveType type){
	if (auto pawn = getPawn(start)){
		int direction = 1;
		if (pawn->owner == COMPUTER)
			direction = -1;
		if(type == BEAT){
			sf::Vector2i beaten_pawn(start.x + (finish.x - start.x)/2, start.y + direction);
			getPawn(beaten_pawn).reset();
			setPawn(beaten_pawn, nullptr);

		}
		setPawn(start, nullptr);
		setPawn(finish, pawn);
		pawn->coordinates = finish;
		return pawn;
	}
	return nullptr;
}

MoveType Board::checkMove(sf::Vector2i& start, sf::Vector2i& finish){
	MoveType result = INVALID;
	if(finish.x >= 0 && finish.x <= 7 && finish.y >= 0 && finish.y <=7){
		if(std::shared_ptr<Pawn> pawn = getPawn(start)){
			int direction = 1;
			if (pawn->owner == COMPUTER)
				direction = -1;
			if (finish.y == start.y + direction){
				if (finish.x == start.x + 1 || finish.x == start.x - 1){
					if (!getPawn(finish)){
						result = NORMAL;
					}
				}
			}
			else if (finish.y == start.y + 2*direction){
				if (finish.x == start.x + 2 || finish.x == start.x - 2){
					if (!getPawn(finish)){
						sf::Vector2i beaten_pawn(start.x + (finish.x - start.x)/2, start.y + direction);
						if (getPawn(beaten_pawn)){
							if (getPawn(beaten_pawn)->owner == otherPlayer(pawn->owner)){
								result = BEAT;
							}
						}
					}
				}
			}
		}
	}
	return result;
}

std::vector<Move>* Board::getAvailibleMoves(OwningPlayer player, const std::vector<std::weak_ptr<Pawn>>& pawn_vector){
	std::vector<Move>* move_vector = new std::vector<Move>;
	for (auto pawn: pawn_vector){
		auto new_moves = getAvailibleMoves(player, pawn);
		if(!new_moves->empty())
			move_vector->insert(move_vector->end(), new_moves->begin(), new_moves->end());
		delete new_moves;
	}
	return move_vector;
}

std::vector<Move>* Board::getAvailibleMoves(OwningPlayer player, const std::weak_ptr<Pawn>& pawn_weak){
	std::vector<Move>* move_vector = new std::vector<Move>;
	sf::Vector2i start, finish;
	int direction = 1;
	if (auto pawn = pawn_weak.lock()){
		if (player == COMPUTER)
			direction = -1;
		start = pawn->coordinates;
		for (int k: {1,2}){
			for (int l: {-1,1}){
				finish = start + sf::Vector2i(l*k, k*direction);
				MoveType result = checkMove(start, finish);
				if (result != INVALID){
					Move new_move = Move(start, finish, result);
					move_vector->push_back(new_move);
				}
			}
		}
	}
	return move_vector;
}

int Board::getScore(OwningPlayer player, const std::vector<std::weak_ptr<Pawn>>& pawn_vector){
	int score = 0;
	for (auto pawn_weak: pawn_vector){
		if (auto pawn = pawn_weak.lock()){
			std::vector<Move>* move_vector = new std::vector<Move>;
			int x = pawn->coordinates.x;
			int y = pawn->coordinates.y;
			score += 5;
			if (player == HUMAN){
				if (y == 2 || y == 3)
					score += 1;
				else if (y == 4 || y == 5)
					score += 3;
				else if (y == 6 || y == 7)
					score += 17;
			}
			else{
				if (y == 5 || y == 4)
					score += 1;
				else if (y == 3 || y == 2)
					score += 3;
				else if (y == 1 || y == 0)
					score += 17;
			}
			if ((x == 0 || x == 7) && (y == 0 || y == 7))
				score += 2;
			else if ((x == 1 || x == 6) && (y == 1 || y == 6))
				score += 1;
			move_vector = getAvailibleMoves(player, pawn);
			if (!move_vector->empty()){
				for (auto tested_move: *move_vector){
					if (tested_move.type == BEAT)
						score += 30;
				}
			}
			delete move_vector;
		}
	}
	return score;
}