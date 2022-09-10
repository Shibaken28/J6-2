# include "Needle.hpp"

namespace MyGame {
	Needle::Needle() {
	}

	Needle::Needle(Vec2 pos, int deg) {
		motion = new NonMotion(pos);
		degree = deg;
		init();
	}


	Needle::Needle(Vec2 pos, Size s, int deg) {
		motion = new NonMotion(pos);
		degree = deg;
		size = s;
		init();
	}

	void Needle::init() {
		isRigid = false;
		isFixed = false;
		position = motion->getPos();
		setTexture(TextureAsset(U"Needle"));
	}

	void Needle::update(){
		motion->move();
		considerVelocity = motion->getDelta();

	}

	GameObjectHitNode Needle::getHitNode(){
		GameObjectHitNode node(GameObjectType::Needle);
		Vec2 p0 = getRect().topCenter() - getCenter();
		Vec2 p1 = getRect().br() - getCenter();
		Vec2 p2 = getRect().bl() - getCenter();
		p0.rotate(degree * (1_deg));
		p1.rotate(degree * (1_deg));
		p2.rotate(degree * (1_deg));
		p0.moveBy(position + size / 2);
		p1.moveBy(position + size / 2);
		p2.moveBy(position + size / 2);
		node.shapes.push_back(Triangle(p0, p1, p2));
		return node;
	}

	void Needle::hitCheck(const GameObjectHitNode& node){
		
	}

	void Needle::setTexture(Texture t) {
		texture = t;
	}

	void Needle::draw() const{
		texture.resized(size).rotated(degree * (1_deg)).draw(position);
	}

	TrollNeedle::TrollNeedle(Vec2 pos, Size s, int deg,Rect rect,Vec2 vel) {
		motion = new TriggerMotion(pos, vel);
		degree = deg;
		size = s;
		trigger = rect;
		Needle::init();
	}

	void TrollNeedle::hitCheck(const GameObjectHitNode& node) {
		if (node.objectType == GameObjectType::Player) {
			Rect rect = std::get<Rect>(node.shapes[0]);
			if (trigger.intersects(rect)) {
				motion->triggered();
			}
		}
	}
}

