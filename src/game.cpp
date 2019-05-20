#include "game.h"

Game::Game(){
	textures[0].loadFromFile("./graphics/board.jpg");
	textures[1].loadFromFile("./graphics/black.png");
	textures[2].loadFromFile("./graphics/red.png");
	textures[3].loadFromFile("./graphics/black_king.png");
	textures[4].loadFromFile("./graphics/red_king.png");

	sprites[0].setTexture(textures[0]);
	sprites[1].setTexture(textures[1]);
	sprites[2].setTexture(textures[2]);
	sprites[3].setTexture(textures[3]);
	sprites[4].setTexture(textures[4]);
	// for (int i = 0; i < )
}

void Game::start(){
	window.create(sf::VideoMode(size, size), "Miloszland-Checkers");
	window.draw(sprites[0]);
	window.display();
}

void Game::play(){
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}