#ifndef GAME_H
#define GAME_H

#include "pawn.h"
#include "board.h"
#include <vector>

class Game{
public:
	std::vector<Pawn> human_pawns;
	std::vector<Pawn> computer_pawns;
	Board game_board;

};
#endif