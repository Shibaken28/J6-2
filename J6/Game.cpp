# include "Game.hpp"

Game::Game(const InitData& init)
	: IScene{ init }
{
	gameManager = new MyGame::GameManager();
}

void Game::update()
{
	gameManager -> update();
	//Print << gameManager -> fieldMap->isInWall(Cursor::PosF());
}

void Game::draw() const{
	gameManager -> draw();
}
