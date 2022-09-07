# pragma once
# include "GameObjects.cpp"

namespace MyGame{
	class GameManager {
	private:
		Player* player;
		int16 chipSizeInt;
		Size chipSize;
		Array<GameObject*> gameObjects;
	public:
		FieldMap* fieldMap;
		GameManager() {
			init();
		}
		void init() {
			gameObjects.clear();
			chipSizeInt = 64;
			chipSize = Size(chipSizeInt, chipSizeInt);
			player = new Player();
			player->setSize(Size(32,32));
			player->setPosition(Vec2(32, 32));
			player->setTexture(TextureAsset(U"MrJ"));
			fieldMap = new FieldMap(128,128);
			fieldMap->setBlock(0, 4);
			fieldMap->setBlock(1, 4);
			fieldMap->setBlock(2, 4);
			fieldMap->setBlock(2, 7);
			fieldMap->setBlock(3, 7);
			fieldMap->setBlock(4, 7);
			fieldMap->setBlock(5, 7);
			fieldMap->setBlock(6, 7);
			fieldMap->setBlock(7, 7);
			fieldMap->setBlock(7, 6);
			fieldMap->setBlock(7, 5);
			fieldMap->setBlock(7, 4);
			fieldMap->setBlock(7, 3);
			fieldMap->setBlock(7, 2);
			fieldMap->setBlock(7, 9);
			fieldMap->setBlock(7, 10);
			fieldMap->setBlock(6, 10);
			fieldMap->setBlock(7, 11);
			addNeedle(Vec2(4,6),0);
			addNeedle(Vec2(4.5f, 5), 0);
			addNeedle(Vec2(5, 6), 0);
			addNeedle(Vec2(6.5f, 6.5f),Size(32,32), 0);
			addNeedle(Vec2(10, 5), 0);
		}
		void draw() const{
			player->draw();
			fieldMap->draw();
			for (auto& obs : gameObjects) {
				obs->draw();
			}
		}
		void update() {
			for (auto& obs : gameObjects) {
				obs->update();
				player->isHit(obs->getNode());
			}
			player->update();
			fieldMap->update();
			fieldMap->wallResistance(*player);
		}
		void addNeedle(Vec2 pos,int deg) {
			gameObjects.push_back(new Needle(pos*chipSizeInt,deg));
		}
		void addNeedle(Vec2 pos,Size s, int deg) {
			gameObjects.push_back(new Needle(pos * chipSizeInt,s, deg));
		}
	};

}
