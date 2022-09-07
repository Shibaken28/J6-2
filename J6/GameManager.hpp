#pragma once
# include <Siv3D.hpp>
# include "GameObject.hpp"
# include "GameObjectPlayer.hpp"

namespace MyGame {
	class GameManager {
	private:
		Player* player;
	public:
		GameManager();
		void init();
		void draw() const;
		void update();
	};

}
