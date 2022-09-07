# pragma once
# include <Siv3D.hpp>
# include "GameObject.cpp"

namespace MyGame {

	class Player : DynamicObject {
	private:
		int16 jumpMax;
		Vec2 Gravity;
		Texture texture;
	public:
		Player() {
			init();
		}
		void init() {
			jumpMax = 2;
		}
		void update() override {
			Velocity += Gravity;
			position += Velocity;
		}
		void isHit(GmaeObjectNode node) override {

		}
		GmaeObjectNode getNode() override {
			return GmaeObjectNode();
		}
		void draw() const override {
			Rect(position.asPoint(), size)(texture).draw();
		}
		void setGravity(Vec2 v) {
			Gravity = v;
		}
		void setPosition(Vec2 v) {
			position = v;
		}
		void setSize(Size s) {
			size = s;
		}
		Vec2 getPosition() {
			return position;
		}
		Size getSize() {
			return size;
		}
		void setTexture(Texture t) {
			texture = t;
		}
	};
}
