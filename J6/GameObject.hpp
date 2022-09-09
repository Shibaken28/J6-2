# pragma once
# include "Common.hpp"


namespace MyGame {

	bool hasCommonRange(double l0, double r0, double l1, double r1);
	bool isMovingRectHit(const Rect& rect0, const Point& var0, const Rect& rect1, const Point& var1, bool& isHitX, bool& isHitY, double& hitTime, Point& revert);
	
	enum class GameObjectType :int {
		Player, Needle
	};

	using objectShape = std::variant<Triangle>;

	struct GameObjectNode {
		GameObjectType objectType;
		Array<objectShape> shapes;
		GameObjectNode();
		GameObjectNode(GameObjectType type);
	};

	class GameObject {
	public:
		virtual void update() = 0;
	};

}

