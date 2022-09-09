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

	void Motion::stopX() {

	}
	void Motion::stopY() {

	}

	void Motion::setPos(Vec2 v) {
		Print << v;
		pos = v;
	}

	NonMotion::NonMotion(Vec2 v):Motion(v) {}

	void NonMotion::move(){

	};

	void NonMotion::stopX() {
	}

	void NonMotion::stopY() {
	}

	PlayerMotion::PlayerMotion(Vec2 v) :Motion(v){
		jumpKey = KeyZ;
		leftKey = KeyLeft;
		rightKey = KeyRight;
		jumpMax = 2;
		fallMaxSpeed = 64 * 60;
		jumpPower = 20 * 60;
		Gravity = Vec2(0.0f, 1.0f * 60 * 60);
		moveSpeed = 6 * 60;
	}

	void PlayerMotion::move() {
		Vec2 preVelocity = velocity;
		velocity += Gravity * Scene::DeltaTime();
		if (jumpKey.down()) {
			velocity.y = -jumpPower;
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


	RoundMotion::RoundMotion(Vec2 v, Vec2 d, double t) :Motion(v) {
		this->p1 = v;
		this->d = d;
		roundTime = t;
		pos = p1 + d * Periodic::Triangle0_1(roundTime * 1s);
	}

	void RoundMotion::move() {
		Vec2 nextPos = p1 + d * Periodic::Triangle0_1(roundTime*1s);
		delta = nextPos - pos;
		//Print << pos << U" " << nextPos << U" " << delta;
		//pos = nextPos;
	}

	void RoundMotion::stopX() {

	}

	void RoundMotion::stopY() {

	}

}

