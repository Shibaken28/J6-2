# pragma once
# include "Common.hpp"


namespace MyGame {
	class Block : public EntityObject {
	private:
		Texture texture;
	public:
		GameObjectHitNode getHitNode() override;
		void hitCheck(GameObjectHitNode&) override;
		void draw() const override;
		void update() override;
		Block();
		Block(Vec2 v, Size s, int t = 0);
		void setTexture(Texture t);
		void init();
	};
}

