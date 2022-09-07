# pragma once
# include "GameObjects.cpp"

namespace MyGame{
	class GameManager {
	private:
		Player* player;
		FieldMap* fieldMap;
	public:
		GameManager() {
			init();
		}
		void init() {
			player = new Player();
			player->setSize(Size(32, 32));
			player->setPosition(Vec2(32, 32));
			player->setTexture(TextureAsset(U"MrJ"));
			fieldMap = new FieldMap(128,128);
			fieldMap->setBlock(0, 4);
			fieldMap->setBlock(1, 4);
			fieldMap->setBlock(2, 4);
			fieldMap->setBlock(5, 7);
			fieldMap->setBlock(6, 7);
			fieldMap->setBlock(7, 7);
			fieldMap->setBlock(7, 6);
		}
		void draw() const{
			player->draw();
			fieldMap->draw();
		}
		void update() {
			player->update();
			fieldMap->update();
		}
	};

}
