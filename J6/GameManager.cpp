# pragma once
# include "GameObjects.cpp"

namespace MyGame{
	class GameManager {
	private:
		Player* player;
	public:
		GameManager() {
			init();
		}
		void init() {
			player = new Player();
			player->setSize(Size(32, 32));
			player->setPosition(Vec2(32, 32));
			player->setTexture(TextureAsset(U"MrJ"));
			player->setGravity(Vec2(0,0.8f));
		}
		void draw() const{
			player->draw();
		}
		void update() {
			player->update();
		}
	};

}
