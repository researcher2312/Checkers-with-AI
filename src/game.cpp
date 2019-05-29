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
				if (j < 3){
					pawns.emplace(pawns.end(), i, j, human);
					game_board.field[i][j] = &pawns.back();
				}
				else if (j > 4){
					pawns.emplace(pawns.end(), i, j, computer);
					game_board.field[i][j] = &pawns.back();
				}
			}
		}
	}
}

void Game::start(){
	window.create(sf::VideoMode(board_size, board_size), "Miloszland-Checkers");
	view();
}

void Game::play(){
	sf::Vector2i mouse_position, start, finish;
	sf::Vector2i* updated_vector;
	Pawn* active_pawn = nullptr;
	bool mouse_pressed=false;
	while (window.isOpen()){
		mouse_pressed = pollEvents(mouse_position);
		if (mouse_pressed){
			if(mouse_position.x > border_size && mouse_position.x < board_size - border_size &&
					mouse_position.y > border_size && mouse_position.y < board_size - border_size){
				if (!active_pawn){
					updated_vector = &start;
				}
				else{
					updated_vector = &finish;
				}
				updated_vector->x = (mouse_position.x - border_size) / field_size + 1;
				updated_vector->y = (mouse_position.y - border_size) / field_size + 1;
				updated_vector->y = 9 - updated_vector->y;
				if (active_pawn){
					//std::cerr << "checking move " << start.x << start.y << '-' << finish.x << finish.y << '\n';
					if (game_board.moveIsValid(start, finish)){
						//active_pawn->move(finish);
						std::cerr << "valid move\n";
					}
					active_pawn = nullptr;
				}
				else {
					active_pawn = game_board.getPawn(start);
				}
			}
		}
	}
}

bool Game::pollEvents(sf::Vector2i& mouse_position){
	sf::Event event;
	while (window.pollEvent(event)){
		if (event.type == sf::Event::Closed){
			window.close();
			return false;
		}
		if (event.type == sf::Event::MouseButtonPressed){
			if (event.mouseButton.button == sf::Mouse::Left){
				mouse_position.x = event.mouseButton.x;
				mouse_position.y = event.mouseButton.y;
				return true;
			}
		}
	}
	return false;
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