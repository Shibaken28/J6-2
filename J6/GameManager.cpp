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
		player->position = Point(32, 32);
		fieldMap = new FieldMap;// (128, 128);
		gameObjects.push_back(new Block(Vec2(128,128),Size(64,64)));
		gameObjects.push_back(new Block(Vec2(128+64, 128), Size(64, 64)));
		gameObjects.push_back(new Block(Vec2(128+128, 128), Size(64, 64)));
		gameObjects.push_back(new Block(Vec2(128 + 128, 128+64), Size(64, 64)));
		gameObjects.push_back(new Block(Vec2(128 + 128, 128+128), Size(64, 64)));
		gameObjects.push_back(new Block(Vec2(128 + 128, 128+196), Size(64, 64)));
		gameObjects.push_back(new Block(Vec2(128 + 196, 128 + 206), Size(64, 64)));
		gameObjects.push_back(new Block(Vec2(128 + 260, 128 + 216), Size(64, 64)));
		gameObjects.push_back(new Block(Vec2(128 + 300, 128 + 226), Size(64, 64)));
	}
	void GameManager::update() {
		player->update();
		for (const auto& obj : gameObjects) {
			obj->update();
		}
		player->materialCheck(gameObjects);
		for (const auto& obj : gameObjects) {
			obj->materialCheck(gameObjects);
		}
		player->ApplyMove();
		for (const auto& obj : gameObjects) {
			obj->ApplyMove();
		}
		for (const auto obj : gameObjects) {
			player->hitCheck(obj->getHitNode());
		}

	}
	void GameManager::draw() const{
		player->draw();
		for (const auto& obj : gameObjects) {
			obj->draw();
		}
	}
}
