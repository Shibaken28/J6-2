# include "EntityObject.hpp"


namespace MyGame {
	void EntityObject::materialCheck(Array<EntityObject*> &objects) {
		if (not isRigid) {
			fixedPosition = position + considerVelocity;
			return;
		}
		if (isFixed) {
			fixedPosition = position+ considerVelocity;
			return;
		}
		double hitTimeX = 100;
		double hitTimeY = 100;
		Point revert(0,0);
		Point inertia(0,0);
		for (auto& obj : objects) {
			if (obj == this)continue;
			if (not obj->isFixed)continue;
			if (considerVelocity.x > 0) {
				if (Rect(position, size).moveBy(1, 0).intersects(obj->getRect())) {
					considerVelocity.x = 0;
					motion->stopX();
					//considerVelocity += obj->considerVelocity;
				}
			}
			if (considerVelocity.x < 0) {
				if (Rect(position, size).moveBy(-1, 0).intersects(obj->getRect())) {
					considerVelocity.x = 0;
					motion->stopX();
					//considerVelocity += obj->considerVelocity;
				}
			}
			if (considerVelocity.y > 0) {
				if (Rect(position, size).moveBy(0, 1).intersects(obj->getRect())) {
					considerVelocity.y = 0;
					motion->stopY();
					//considerVelocity += obj->considerVelocity;
				}
			}
			if (considerVelocity.y < 0) {
				if (Rect(position, size).moveBy(0, -1).intersects(obj->getRect())) {
					considerVelocity.y = 0;
					motion->stopY();
					//considerVelocity += obj->considerVelocity;
				}
			}
			if (Rect(position, size).moveBy(0, 1).intersects(obj->getRect()) && position.y < obj->position.y) {
				if (inertia.isZero()) {
					inertia = obj->considerVelocity;
				}
			}
			if (Rect(position, size).moveBy(1, 0).intersects(obj->getRect()) && obj->considerVelocity.x<0 ) {
				if (inertia.isZero()) {
					inertia = obj->considerVelocity;
				}
			}
			if (Rect(position, size).moveBy(-1,0).intersects(obj->getRect()) && obj->considerVelocity.x > 0) {
				if (inertia.isZero()) {
					inertia = obj->considerVelocity;
				}
			}
		}
		considerVelocity += inertia;

		for (auto& obj : objects) {
			if (obj == this)continue;
			if (not obj->isFixed)continue;
			bool isHitX = false;
			bool isHitY = false;
			double hitTime = 100;
			Point rev;
			if (isMovingRectHit(getRect(), considerVelocity, obj->getRect(), obj->considerVelocity, isHitX, isHitY, hitTime, rev)) {
				if (isHitY && hitTime < hitTimeY) {
					hitTimeY = hitTime;
					revert.y = rev.y;
				}
				if (isHitX && hitTime < hitTimeX) {
					hitTimeX = hitTime;
					revert.x = rev.x;
				}
			}
		}
		fixedPosition = position + considerVelocity + revert;
		if (hitTimeX < 100) {
			motion->stopX();
		}
		if (hitTimeY < 100) {
			motion->stopY();
		}
	}

	void EntityObject::ApplyMove() {
		motion->setPos(fixedPosition);
		position = fixedPosition;
	}

	Rect EntityObject::getRect() {
		return Rect(position, size);
	}

	Point EntityObject::getCenter() {
		return position + size / 2;
	}

}


