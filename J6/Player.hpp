# pragma once
# include <Siv3D.hpp>
# include "EntityObject.hpp"

namespace MyGame {
	class Player : public EntityObject {
	public:
		int jumpMax;
		Vec2 Gravity;
		double moveSpeed;
		double jumpPower;
		bool deathRequest;
		bool isDead;
	private:
		Texture texture;
		double fallMaxSpeed;
	public:
		Player();
		void init();
		GameObjectHitNode getHitNode() override;
		void hitCheck(const GameObjectHitNode&) override;
		void update() override;
		void draw() const override;
		void death();
		void setTexture(Texture t);
	};
}

