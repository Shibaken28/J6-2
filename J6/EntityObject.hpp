# pragma once
# include <Siv3D.hpp>
# include "Motion.hpp"
# include "GameObject.hpp"


namespace MyGame{
	class EntityObject : public GameObject {
	public:
		bool isAlive = true;
		bool isShow = true;
		bool isRigid = false;
		bool isFixed = false;
		Motion *motion;
		Point position{ 0,0 };
		Point fixedPosition{ 0,0 };
		Size size{ 64,64 };
		Point considerVelocity{0,0};
	public:
		virtual GameObjectHitNode getHitNode() = 0;
		virtual void draw() const = 0;
		virtual void update() = 0;
		virtual void hitCheck(const GameObjectHitNode&) = 0;
		void materialCheck(Array<EntityObject*>&);
		void ApplyMove();
		Rect getRect();
		Point getCenter();
	};
}

