#ifndef PAWN_H
#define PAWN_H

#include <SFML/Graphics.hpp>

enum OwningPlayer{
	human,
	computer,
};

enum PawnLevel{
	normal,
	king,
};

class Pawn{
public:
	Pawn(int, int, OwningPlayer);
	void lightUp();
	OwningPlayer player;
	PawnLevel level = normal;
	float x;
	float y;
};

#endif