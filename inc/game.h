#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "pawn.h"
#include "board.h"

const int size = 612;

class Game{
public:
	Game();
	void start();
	void play();
	void end();
	sf::RenderWindow window;
	sf::Texture textures[5];
	sf::Sprite sprites[5];
	std::vector<Pawn> human_pawns;
	std::vector<Pawn> computer_pawns;
	Board game_board;

};
#endif