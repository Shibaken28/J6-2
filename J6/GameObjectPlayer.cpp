
# include "GameObjectPlayer.hpp"

namespace MyGame {

	class Player : DynamicObject {
	public:
		Player() {
			init();
		}
		void init() {
			jumpMax = 2;
			fallMaxSpeed = 8;
			keyJump = KeyZ;
		}
		void update() override {
			Velocity += Gravity;
			Clamp(Velocity.y, -fallMaxSpeed, fallMaxSpeed);
			position += Velocity;
			if (keyJump.down()) {
				Print << U"Jump2";
				Velocity.y = -jumpPower;
			}
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
