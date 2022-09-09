# include "Player.hpp"

namespace MyGame {
	Player::Player() {
		init();
	}
	void Player::init() {
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
	}
	void Player::update(){
		if (deathRequest) {
			death();
		}
		jump();
		//horizonMove();
		Velocity += Gravity * Scene::DeltaTime();
		Vec2 preVelocity = Velocity;
		if (Velocity.y >= fallMaxSpeed)Velocity.y = fallMaxSpeed;
		considerVelocity = ((preVelocity + Velocity) * Scene::DeltaTime() / 2).asPoint();
	}
	void Player::death() {
		deathRequest = false;
		//position = Vec2(100,100);
	}
	void Player::hitCheck(GameObjectHitNode &node){
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
		return GameObjectHitNode();
	}
	void Player::draw() const{
		Rect(position.asPoint(), size)(texture).draw();
	}
	void Player::setTexture(Texture t) {
		texture = t;
	}
}

