#ifndef BOARD_H
#define BOARD_H

#include "pawn.h"


class Board{
public:
	Pawn* field[8][8]= {0};
};
#endif