#ifndef PAWN_H
#define PAWN_H

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
	Pawn(OwningPlayer, int, int);
	void move();
	void lightUp();
	OwningPlayer player;
	PawnLevel level;
	int x;
	int y;
};

#endif