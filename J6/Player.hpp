# pragma once
# include "Common.hpp"


namespace MyGame {
	class Player : public EntityObject {
	public:
		int jumpMax;
		Vec2 Gravity;
		double moveSpeed;
		double jumpPower;
		bool deathRequest;
	private:
		Texture texture;
		double fallMaxSpeed;
	public:
		Player();
		void init();
		GameObjectHitNode getHitNode() override;
		void hitCheck(GameObjectHitNode&) override;
		void update() override;
		void draw() const override;
		void death();
		void jump();
		void setTexture(Texture t);
	};
}

