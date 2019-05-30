#include "game.h"
#include <iostream>

void delay(int miliseconds){
	sf::Clock clock;
	clock.restart();
	while(1){
		if(clock.getElapsedTime().asMilliseconds() > miliseconds)
			break;
	}
}

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
				int new_x = border_size + i * field_size + 5;
				int new_y = border_size + (7-j) * field_size + 5;
				Pawn* new_pawn;
				if (j < 3){
					new_pawn = new Pawn(new_x, new_y, human);
					game_board.field[i][j] = new_pawn;
				}
				else if (j > 4){
					new_pawn = new Pawn(new_x, new_y, computer);
					game_board.field[i][j] = new_pawn;
				}
				pawns.push_back(new_pawn);
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
		if (pawn->player == human)
			sprite_number = 1;
		else
			sprite_number = 2;
		sprites[sprite_number].setPosition(pawn->x, pawn->y);
		window.draw(sprites[sprite_number]);
	}
	window.display();
}

void Game::movePawn(Pawn* pawn, sf::Vector2i& start, sf::Vector2i& finish){
	float distance_x = (finish-start).x * field_size / 10;
	float distance_y = (finish-start).y * field_size / 10;
	game_board.field[start.x][start.y] = nullptr;
	game_board.field[finish.x][finish.y] = pawn;
	for (int i = 0; i <= 10; ++i){
		pawn->x += distance_x;
		pawn->y -= distance_y;
		delay(20);
		view();
	}
	view();
	
}
