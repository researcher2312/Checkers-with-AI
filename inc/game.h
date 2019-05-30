#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "pawn.h"
#include "board.h"

const float board_size = 800;
const float field_size = 77.5;
const float border_size = 91;
class Game{
public:
	Game();
	void start();
	void play();
	void end();
	void view();
	int manualMove(OwningPlayer player);
	void movePawn(std::shared_ptr<Pawn> pawn_ptr, sf::Vector2i& start, sf::Vector2i& finish, MoveType type);
	bool pollEvents(sf::Vector2i& mouse_position);
	sf::RenderWindow window;
	sf::Texture textures[5];
	sf::Sprite sprites[5];
	sf::Image icon;
	std::vector<std::weak_ptr<Pawn>> pawns;
	// std::vector<Pawn*> activepawns;
	// std::vector<Pawn*> pawns;

	Board game_board;
	OwningPlayer active_player = human;
};
#endif