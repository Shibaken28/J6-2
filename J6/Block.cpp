# include "Block.hpp"

namespace MyGame {
	Block::Block() {
		init();
	}

	Block::Block(Vec2 v, Size s) {
		motion = new NonMotion(v);
		size = s;
		init();
	}

	void Block::init() {
		isRigid = true;
		isFixed = true;
		position = motion->getPos();
		setTexture(TextureAsset(U"Block"));
	}

	GameObjectHitNode Block::getHitNode() {
		return GameObjectHitNode();
	}

	void Block::hitCheck(const GameObjectHitNode& gameObjectHitNode) {

	}

	void Block::draw() const {
		Rect(position, size)(texture).draw();
	}

	void Block::update(){
		motion->move();
		considerVelocity = motion->getDelta();
		//considerVelocity = (Velocity * Scene::DeltaTime()).asPoint();
	};

	void Block::setTexture(Texture t) {
		texture = t;
	}

}

