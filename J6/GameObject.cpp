# pragma once
# include <Siv3D.hpp>

namespace MyGame {

	enum class GameObjectType :int16 {
		Player
	};

	struct GmaeObjectNode {
		GameObjectType objectType;
	};


	class GameObject {
	public:
		bool isAlive;
	public:
		virtual void isHit(GmaeObjectNode) = 0;
		virtual void update() = 0;
		virtual GmaeObjectNode getNode() = 0;
		virtual void draw() const = 0;
	};

	class DynamicObject : GameObject {
	protected:
		Vec2 position;
		Vec2 Velocity;
		Size size;

	};

	class Field : GameObject {

	};

	class Block : Field {

	};

	class FieldMap {
	public:
		Grid<Field> map;

	};


}
