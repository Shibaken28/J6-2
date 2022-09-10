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
		player->position = Point(32, 400);
		fieldMap = new FieldMap;// (128, 128);
		for (int i = 0; i < 2000; i += 64) {
			gameObjects.push_back(new Block(Vec2(i, 512), Size(64, 64)));
		}
		gameObjects.push_back(new Block(Vec2(128*6, 256), Size(64, 64)));
		gameObjects.push_back(new TrollNeedle(Vec2(256, 512 - 64), Size(64, 64), 0, Rect(256, 0, 64, 800), Vec2(0, -32 * 60)));
		gameObjects.push_back(new TrollNeedle(Vec2(512-64, 512 - 64), Size(64, 64), 0, Rect(512+128, 512-64, 400, 64), Vec2(32 * 60,0)));
		for (int i = 512-64; i > 100; i -= 64) {
			gameObjects.push_back(new TrollNeedle(Vec2(512+256+512, i), Size(64, 64), 270, Rect(512 + 512+256-128-64, 64, 400, 1000), Vec2(-6 * 60, 0)));
			gameObjects.push_back(new Block(Vec2(512 + 256 + 512+64, i), Size(64, 64)));
		}
	}
	void GameManager::update() {
		if (player->isDead) {
			if(KeyR.down())init();
		}
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
		camera.jumpTo(Vec2{ player->position.x, 300 }, 1.0);
		camera.update();

	}
	void GameManager::draw() const{
		{
			const auto t = camera.createTransformer();
			player->draw();
			for (const auto& obj : gameObjects) {
				obj->draw();
			}
		}
	}
}
