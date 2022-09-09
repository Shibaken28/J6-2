# pragma once
# include "GameObjects.cpp"

namespace MyGame{
	class GameManager {
	private:
		Player* player;
		int chipSizeInt;
		Size chipSize;
		Array<GameObject*> gameObjects;
		Camera2D camera{ Vec2{ 0, 0 }, 1.0 };
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
			player->setPosition(Vec2(102, 32));
			player->setTexture(TextureAsset(U"MrJ"));
			fieldMap = new FieldMap(128,128);
			fieldMap->setBlock(0, 0, 500);
			fieldMap->setBlock(1, 0, 500);
			fieldMap->setBlock(2, 0, 500);
			fieldMap->setBlock(3, 0, 500);
			fieldMap->setBlock(4, 0, 500);
			fieldMap->setBlock(5, 0, 500);
			fieldMap->setBlock(6, 0, 500);
			fieldMap->setBlock(6, 4, 500);
			fieldMap->setBlock(6, 5, 800);
			//fieldMap->setBlock(5, 7);
			fieldMap->setBlock(7, 8);
			fieldMap->setBlock(7, 6);
			fieldMap->setBlock(7, 5);
			fieldMap->setBlock(7, 3);
			fieldMap->setBlock(7, 2,1100);
			fieldMap->setBlock(7, 9);
			fieldMap->setBlock(7, 10);
			fieldMap->setBlock(6, 9,300);
			fieldMap->setBlock(7, 11);
			addNeedle(Vec2(5,6),0);
			addNeedle(Vec2(5.5f, 5), 0);
			addNeedle(Vec2(6, 6), 0);
			addNeedle(Vec2(8.0f, 6.5f),Size(32,32), 0);
			addNeedle(Vec2(10, 5), 0);
			for (int i = 0; i < 1000; i++) {
				addNeedle(Vec2(i*0.1f, 9-i*i*0.0001), i*4);
			}
		}
		void draw() const{
			{
				const auto t = camera.createTransformer();
				player->draw();
				fieldMap->draw();
				for (auto& obs : gameObjects) {
					obs->draw();
				}
			}
		}
		void update() {
			camera.update();
			camera.jumpTo(player->position, 1.0f);
			for (auto& obs : gameObjects) {
				obs->update();
				player->isHit(obs->getNode());
			}
			player->update();
			fieldMap->update();
			fieldMap->wallResistance(*player);
			/*for (auto& obs : *fieldMap) {
				if (obs->isRigid) {
					bool isHitX, isHitY;
					double hitTime;
					Vec2 revert;
					isMovingRectHit(player->rect(),player->Velocity, obs->rect(), obs->Velocity,isHitX,isHitY,hitTime,revert);
					player->position -= revert;
				}
			}*/
		}
		void addNeedle(Vec2 pos,int deg) {
			gameObjects.push_back(new Needle(pos*chipSizeInt,deg));
		}
		void addNeedle(Vec2 pos,Size s, int deg) {
			gameObjects.push_back(new Needle(pos * chipSizeInt,s, deg));
		}
	};

}
