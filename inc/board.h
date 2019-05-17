#ifndef BOARD_H
#define BOARD_H

struct BoardField{
	int x;
	int y;
	int size;
	Pawn* pawn;
	void lightUp();
};

class Board{
public:
	BoardField[8][8];
};
#endif