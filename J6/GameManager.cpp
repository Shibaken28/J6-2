# include "GameManager.hpp"

namespace MyGame {
	GameManager::GameManager() {
		init();
	}
	void GameManager::init() {
		gameObjects.clear();
		chipSizeInt = 64;
		chipSize = Size(chipSizeInt, chipSizeInt);
		player = new Player();
		player->size = Size(32, 32);
		player->position = Vec2(32, 32);
		fieldMap = new FieldMap;// (128, 128);
		/*
		fieldMap->setBlock(6, 4);
		fieldMap->setBlock(6, 5);
		fieldMap->setBlock(5, 7);
		fieldMap->setBlock(7, 8);
		fieldMap->setBlock(7, 6);
		fieldMap->setBlock(7, 5);
		fieldMap->setBlock(7, 3);
		fieldMap->setBlock(7, 2);
		fieldMap->setBlock(7, 9);
		fieldMap->setBlock(7, 10);
		fieldMap->setBlock(6, 9);
		fieldMap->setBlock(7, 11);
		/*
		addNeedle(Vec2(5, 6), 0);
		addNeedle(Vec2(5.5f, 5), 0);
		addNeedle(Vec2(6, 6), 0);
		addNeedle(Vec2(8.0f, 6.5f), Size(32, 32), 0);
		addNeedle(Vec2(10, 5), 0);
		for (int i = 0; i < 1000; i++) {
			addNeedle(Vec2(i * 0.1f, 9 - i * i * 0.0001), i * 4);
		}
		*/
	}
	void GameManager::update() {

	}
	void GameManager::draw() const{
		player->draw();
	}
}
