# pragma once
# include <Siv3D.hpp>
# include "GameObject.hpp"

namespace MyGame {

	class Player : DynamicObject {
	private:
		int16 jumpMax;
		Vec2 Gravity;
		Texture texture;
		double fallMaxSpeed;
		Input keyJump;
		double jumpPower;
	public:
		Player();
		void init();
		void update() override;
		void isHit(GmaeObjectNode node) override;
		GmaeObjectNode getNode() override;
		void draw() const override;
		void setGravity(Vec2 v);
		void setPosition(Vec2 v);
		void setSize(Size s);
		Vec2 getPosition();
		Size getSize();
		void setTexture(Texture t);
	};
}
