#include "game.h"
#include <iostream>

Game::Game(){
	//texture initialization
	textures[0].loadFromFile("./graphics/board.jpg");
	textures[1].loadFromFile("./graphics/black.png");
	textures[2].loadFromFile("./graphics/red.png");
	textures[3].loadFromFile("./graphics/black_king.png");
	textures[4].loadFromFile("./graphics/red_king.png");
	//sprite initialization
	sprites[0].setTexture(textures[0]);
	for (int i = 1; i < 5; ++i){
		sprites[i].setTexture(textures[i]);
		sprites[i].setScale(0.6,0.6);
	}
	//pawn vector initialization
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if (i%2 == j%2){
				if (j < 3)
					pawns.emplace(pawns.end(), i, j, human);
				else if (j > 4)
					pawns.emplace(pawns.end(), i, j, computer);
			}
		}
	}
}

void Game::start(){
	window.create(sf::VideoMode(board_size, board_size), "Miloszland-Checkers");
	view();
}

void Game::play(){
	sf::Vector2i mouse_position;
	bool mouse_pressed;
	while (window.isOpen()){
		mouse_pressed = 0;
		

	}
}

bool Game::pollEvents(sf::Vector2i& mouse_position){
	sf::Event event;
	while (window.pollEvent(event)){
		if (event.type == sf::Event::Closed){
			window.close();
			return 0;
		}
		if (event.type == sf::Event::MouseButtonPressed){
			if (event.mouseButton.button == sf::Mouse::Left){
				mouse_position.x = event.mouseButton.x;
				mouse_position.y = event.mouseButton.y;
				return 1;
			}
		}
	}
	return 0;
}

void Game::view(){
	window.clear();
	//draw the board
	window.draw(sprites[0]);
	int sprite_number;
	//draw the pawns
	for(auto pawn: pawns){
		if (pawn.player == human)
			sprite_number = 1;
		else
			sprite_number = 2;
		sprites[sprite_number].setPosition(border_size+(pawn.x)*field_size+5,border_size+(7-pawn.y)*field_size+5);
		window.draw(sprites[sprite_number]);
	}
	window.display();
}