# pragma once
# include "Common.hpp"

class GameObject {
public:
	bool isAlive = true;
	bool isRigid = false;
	Vec2 position{ 0,0 };
	Vec2 Velocity{ 0,0 };
	Size size{ 64,64 };
	Point considerVelocity;
public:
	virtual bool isHit(GameObjectNode) = 0;
	virtual void update() = 0;
	virtual GameObjectNode getNode() = 0;
	virtual void draw() const = 0;
	Rect rect() {
		return Rect(position.asPoint(), size);
	}
};
