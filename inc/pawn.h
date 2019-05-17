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
	Pawn();
	void move();
	void lightUp();
	int position[2];
	OwningPlayer player;
	PawnLevel level;
};

#endif