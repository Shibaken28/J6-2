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
		for (int i = 0; i < 1000; i += 64) {
			gameObjects.push_back(new Block(Vec2(i, 512), Size(64, 64)));
		}
		gameObjects.push_back(new Needle(Vec2(256, 512-64), Size(64, 64), 0));
		gameObjects.push_back(new TrollNeedle(Vec2(512, 512 - 64), Size(64, 64),0,Rect(512,0,64,904), Vec2(0,-64*60)));
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

		for (const auto obj : gameObjects) {
			obj->hitCheck(player->getHitNode());
		}

	}
	void GameManager::draw() const{
		player->draw();
		for (const auto& obj : gameObjects) {
			obj->draw();
		}
	}
}
