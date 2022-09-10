# include "Player.hpp"

namespace MyGame {
	Player::Player() {
		init();
	}

	void Player::init() {
		isRigid = true;
		isDead = false;
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
		if (not isAlive)return;
		if (deathRequest) {
			death();
		}
		motion->move();
		considerVelocity = motion->getDelta();
	}

	void Player::death() {
		effect.add([pos = position](double t)
			{
				for (auto i : step(8))
				{
					const double theta = (i * 45_deg);

					const double e = EaseOutCirc(t);

					const Vec2 vec = OffsetCircular{ pos, e * 150, theta};

					Circle{ vec, 20 }.drawFrame(4 * (1.0f - e), 0, ColorF{1.0f,1.0f,0.0f ,1.0f - t});
				}

				// 1 秒未満なら継続
				return (t < 1.0);
			});
		deathRequest = false;
		isAlive = false;
		isDead = true;
		motion->reset();
		motion->stopX();
		motion->stopY();
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
		effect.update();
		if (not isAlive)return;
		Rect(position, size)(texture).draw();
	}

	void Player::setTexture(Texture t) {
		texture = t;
	}
}

