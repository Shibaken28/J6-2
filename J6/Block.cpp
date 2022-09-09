# include "Block.hpp"

namespace MyGame {
	Block::Block() {
		init();
	}

	Block::Block(Vec2 v, Size s, int t = 0) {
		position = v;
		size = s;
		if (t > 500)Velocity.y = t - 500;
		else Velocity.x = t;
		if (t > 1000) {
			Velocity.x = 400;
			Velocity.y = 400;
		}
		init();
	}

	void Block::init() {
		setTexture(TextureAsset(U"Block"));
	}

	GameObjectHitNode Block::getHitNode() {
		return GameObjectHitNode();
	}

	void Block::hitCheck(GameObjectHitNode& gameObjectHitNode) {

	}

	void Block::draw() const {
		Rect(position.asPoint(), size)(texture).draw();
	}

	void Block::update(){
		considerVelocity = (Velocity * Scene::DeltaTime()).asPoint();
	};

	void Block::setTexture(Texture t) {
		texture = t;
	}

}

