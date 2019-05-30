#include "pawn.h"

OwningPlayer otherPlayer(OwningPlayer current_player){
	if (current_player == human)
		return computer;
	return human;
}

Pawn::Pawn(int x_, int y_, OwningPlayer owner_): owner(owner_), x(x_), y(y_){}

// void Pawn::lightUp(){

// }
