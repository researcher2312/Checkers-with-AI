#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "pawn.h"
#include "board.h"

const int board_size = 800;
const int field_size = 77;
const int border_size = 92;
class Game{
public:
	Game();
	void start();
	void play();
	void end();
	void view();
	bool pollEvents(sf::Vector2i& mouse_position);
	sf::RenderWindow window;
	sf::Texture textures[5];
	sf::Sprite sprites[5];
	std::vector<Pawn> pawns;
	// std::vector<Pawn*> activepawns;
	// std::vector<Pawn*> pawns;

	Board game_board;
	OwningPlayer active_player = human;
};
#endif