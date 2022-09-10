# include "Player.hpp"

namespace MyGame {
	Player::Player() {
		init();
	}

	void Player::init() {
		isRigid = true;
		deathRequest = false;
		jumpMax = 2;
		fallMaxSpeed = 64 * 60;
		//keyJump = KeyZ;
		//keyRight = KeyRight;
		//keyLeft = KeyLeft;
		jumpPower = 20 * 60;
		Gravity = Vec2(0.0f, 1.0f * 60 * 60);
		moveSpeed = 6 * 60;
		setTexture(TextureAsset(U"Mr.J"));
		motion = new PlayerMotion(position);
	}

	void Player::update() {
		if (deathRequest) {
			death();
		}
		motion->move();
		considerVelocity = motion->getDelta();
	}

	void Player::death() {
		deathRequest = false;
		motion->reset();
		motion->setPos(position);
	}

	void Player::hitCheck(const GameObjectHitNode &node){
		//プレイヤーとnodeの当たり判定
		//針
		if (node.objectType == GameObjectType::Needle) {
			Triangle triangle = std::get<Triangle>(node.shapes[0]);
			if (getRect().stretched(-1).intersects(triangle)) {
				deathRequest = true;
			}
		}
	}

	GameObjectHitNode Player::getHitNode() {
		GameObjectHitNode node(GameObjectType::Player);
		node.shapes.push_back(getRect());
		return node;
	}

	void Player::draw() const{
		Rect(position, size)(texture).draw();
	}

	void Player::setTexture(Texture t) {
		texture = t;
	}
}

