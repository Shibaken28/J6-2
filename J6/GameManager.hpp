# pragma once
# include "GameObject.hpp"
# include "Player.hpp"
# include "FieldMap.hpp"

namespace MyGame {
	class GameManager {
	private:
		Player *player;
		int chipSizeInt;
		Size chipSize;
		Array<GameObject*> gameObjects;
		Camera2D camera{ Vec2{ 0, 0 }, 1.0 };
	public:
		FieldMap *fieldMap;
		GameManager();
		void init();
		void draw() const;
		void update();
	};
}

