#ifndef PAWN_H

#include "game.h"

class Pawn{
public:
	Pawn();
	void move();
	void lightUp();
	int position[2];
	OwningPlayer player;
	PawnLevel level;

};

#define PAWN_H value
#endif