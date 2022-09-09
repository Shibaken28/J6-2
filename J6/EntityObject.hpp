# pragma once
# include <Siv3D.hpp>
# include "GameObject.hpp"


namespace MyGame{
	class EntityObject : public GameObject {
	public:
		bool isAlive = true;
		bool isShow = true;
		Vec2 position{ 0,0 };
		Vec2 fixedPosition{ 0,0 };
		Vec2 Velocity{ 0,0 };
		Size size{ 64,64 };
		Point considerVelocity{0,0};
	public:
		virtual GameObjectHitNode getHitNode() = 0;
		virtual void draw() const = 0;
		virtual void update() = 0;
		virtual void hitCheck(GameObjectHitNode&) = 0;
		void materialCheck(Array<EntityObject*>&);
		void ApplyMove();
		Rect getRect();
		Point getCenter();
	};
}

