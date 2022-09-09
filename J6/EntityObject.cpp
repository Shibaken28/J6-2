# include "EntityObject.hpp"



namespace MyGame {
	void EntityObject::materialCheck(Array<EntityObject*>&) {
		
	}
	void EntityObject::hitCheck(GameObjectHitNode&) {
	}
	void EntityObject::ApplyMove() {
	}
	Rect EntityObject::getRect() {
		return Rect(position.asPoint(), size);
	}
	Point EntityObject::getCenter() {
		return position.asPoint() + size / 2;
	}
}


