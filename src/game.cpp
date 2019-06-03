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
	//icon initialization
	icon.loadFromFile("./graphics/red.png");
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
	float new_x, new_y;
	OwningPlayer new_player;
	std::shared_ptr<Pawn> new_pawn_ptr;
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if (i%2 == j%2){
				if (j < 3 || j > 4){
					new_x = border_size + i * field_size + 5;
					new_y = border_size + (7-j) * field_size + 5;
					if (j < 3)
						new_player = HUMAN;
					else if (j > 4)
						new_player = COMPUTER;
					new_pawn_ptr = std::make_shared<Pawn>(i, j, new_x, new_y, new_player);
					game_board.field[i][j] = new_pawn_ptr;
					pawns.push_back(std::weak_ptr(new_pawn_ptr));
					if (new_player == players[0])
						player_pawns[0].push_back(std::weak_ptr(new_pawn_ptr));
					else
						player_pawns[1].push_back(std::weak_ptr(new_pawn_ptr));
				}
			}
		}
	}
}

void Game::start(){
	window.create(sf::VideoMode(board_size, board_size), "Miloszland-Checkers");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	view();
}

int Game::manualMove(OwningPlayer player){
	sf::Vector2i mouse_position, start, finish;
	sf::Vector2i* updated_vector;
	std::shared_ptr<Pawn> active_pawn;
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
				updated_vector->x = (mouse_position.x - border_size) / field_size;
				updated_vector->y = (mouse_position.y - border_size) / field_size;
				updated_vector->y = 7 - updated_vector->y;
				if (active_pawn){
					//std::cerr << start.x << start.y << '-' << finish.x << finish.y << '\n';
					if(active_pawn->owner == player){
						MoveType result = game_board.checkMove(start, finish);
						if (result != INVALID){
							makeMove(start, finish, result);
							return 0;
						}
					}
					active_pawn = nullptr;
				}
				else {
					active_pawn = game_board.getPawn(start);
				}
			}
		}
	}
	return 1;
}

void Game::play(){
	OwningPlayer winner;
	while(1){
		if(manualMove(active_player))
			break;
		active_player = otherPlayer(active_player);
		winner = checkWin(active_player);
		if (winner == HUMAN){
			std::cout << "Wygrałeś!!!\n";
			break;
		}
		else if (winner == COMPUTER){
			std::cout << "LOOOSER :(\n";
			break;
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
	for(auto pawn_ptr: pawns){
		if (auto pawn = pawn_ptr.lock()){
			if (pawn->owner == HUMAN)
				sprite_number = 1;
			else
				sprite_number = 2;
			sprites[sprite_number].setPosition(pawn->x, pawn->y);
			window.draw(sprites[sprite_number]);
		}
	}
	window.display();
}

void Game::makeMove(sf::Vector2i& start, sf::Vector2i& finish, MoveType type){
	if(auto pawn = game_board.movePawn(start, finish, type)){
		float distance_x = ((finish.x - start.x) * field_size) / 10;
		float distance_y = ((finish-start).y * field_size) / 10;
		for (int i = 0; i < 10; ++i){
			pawn->x += distance_x;
			pawn->y -= distance_y;
			delay(20);
			view();
		}
		view();
	}
	
}

OwningPlayer Game::checkWin(OwningPlayer player){
	OwningPlayer winner = NOBODY;
	std::vector<Move>* availible_moves;
	int i = 0;
	for (i = 0; i < 2; ++i){
		if (player == players[i])
			break;
	}
	availible_moves = game_board.getAvailibleMoves(players[i], player_pawns[i]);
	if (availible_moves->empty()){
		winner = otherPlayer(players[i]);
	}
	else {
		int pawn_count = 0;
		for (auto checked_pawn: player_pawns[i]){
			if (checked_pawn.lock())
				++pawn_count;
		}
		if(!pawn_count){
			winner = otherPlayer(players[i]);
		}
	}
	delete availible_moves;
	return winner;
}