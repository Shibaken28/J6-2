# include "Game.hpp"

Game::Game(const InitData& init)
	: IScene{ init }
{
	gameManager = new MyGame::GameManager();
}

void Game::update()
{
	gameManager -> update();
}

void Game::draw() const{
	gameManager -> draw();
}
