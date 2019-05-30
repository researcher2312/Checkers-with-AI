#ifndef PAWN_H
#define PAWN_H

#include <SFML/Graphics.hpp>

enum OwningPlayer{
	human,
	computer,
};

OwningPlayer otherPlayer(OwningPlayer current_player);

enum PawnLevel{
	normal,
	king,
};

class Pawn{
public:
	Pawn(int, int, OwningPlayer);
	void lightUp();
	OwningPlayer owner;
	PawnLevel level = normal;
	float x;
	float y;
};

#endif