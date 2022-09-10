# pragma once
# include "Motion.hpp"

namespace MyGame {
	Motion::Motion(Vec2 v) {
		pos = v;
	}

	Motion::Motion() {
		
	}

	Point Motion::getPos() {
		return pos.asPoint();
	}

	Point Motion::getDelta() {
		return delta.asPoint();
	}

	void Motion::stopX() {}
	void Motion::stopY() {}
	void Motion::reset() {}
	void Motion::onFloor() {}
	void Motion::triggered() {}

	void Motion::setPos(Vec2 v) {
		pos = v;
	}

	NonMotion::NonMotion(Vec2 v):Motion(v) {}

	void NonMotion::move(){

	};

	PlayerMotion::PlayerMotion(Vec2 v) :Motion(v){
		jumpKey = KeyZ;
		leftKey = KeyLeft;
		rightKey = KeyRight;
		jumpMax = 1;
		jumpCount = jumpMax;
		fallMaxSpeed = 64 * 60;
		jumpPower = 18 * 60;
		Gravity = Vec2(0.0f, 1.0f * 60 * 60);
		moveSpeed = 6 * 60;
	}

	void PlayerMotion::move() {
		Vec2 preVelocity = velocity;
		velocity += Gravity * Scene::DeltaTime();
		if (jumpKey.down() && jumpCount>0) {
			velocity.y = -jumpPower;
			jumpCount--;
		}
		if(jumpKey.up()) {
			if (velocity.y < 0) {
				velocity.y /= 2;
			}
		}
		velocity.x = 0;
		if (leftKey.pressed()) {
			velocity.x -= moveSpeed;
		}
		if (rightKey.pressed()) {
			velocity.x += moveSpeed;
		}
		delta = ((preVelocity + velocity) * Scene::DeltaTime() / 2);
	}

	void PlayerMotion::stopX() {
		velocity.x = 0;
	}

	void PlayerMotion::stopY() {
		velocity.y = 0;
	}

	void PlayerMotion::reset() {
		jumpCount = jumpMax;
		velocity.x = 0; velocity.y = 0;
	}

	void PlayerMotion::onFloor() {
		jumpCount = jumpMax;
	}

	RoundMotion::RoundMotion(Vec2 v, Vec2 d, double t) :Motion(v) {
		this->p1 = v;
		this->d = d;
		roundTime = t;
		pos = p1 + d * Periodic::Triangle0_1(roundTime * 1s);
	}

	void RoundMotion::move() {
		Vec2 nextPos = p1 + d * Periodic::Triangle0_1(roundTime*1s);
		delta = nextPos - pos;
	}

	TriggerMotion::TriggerMotion(Vec2 v, Vec2 ve) {
		pos = v;
		velocity = ve;
	}

	void TriggerMotion::move() {
		if (isTriggered)delta = velocity * Scene::DeltaTime();
	}

	void TriggerMotion::triggered() {
		isTriggered = true;
	}
}

