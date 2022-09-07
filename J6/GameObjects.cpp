# pragma once
# include <Siv3D.hpp>

namespace MyGame {

	enum class GameObjectType :int16 {
		Player
	};

	struct GmaeObjectNode {
		GameObjectType objectType;
	};


	class GameObject {
	public:
		bool isAlive;
	public:
		virtual void isHit(GmaeObjectNode) = 0;
		virtual void update() = 0;
		virtual GmaeObjectNode getNode() = 0;
		virtual void draw() const = 0;
	};

	class DynamicObject : GameObject {
	protected:
		Vec2 position{ 0,0 };
		Vec2 Velocity{ 0,0 };
		Size size{ 32,32 };

	};




	class Player : DynamicObject {
	private:
		int16 jumpMax;
		Vec2 Gravity;
		Texture texture;
		double fallMaxSpeed;
		Input keyJump;
		double jumpPower;
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




	class Field : GameObject {

	};

	class Block : Field {

	};

	class FieldMap {
	public:
		Grid<Field> map;

	};


	class GameManager {
	private:
		Player* player;
	public:
		GameManager() {
			init();
		}
		void init() {
			player = new Player();
			player->setSize(Size(32, 32));
			player->setPosition(Vec2(32, 32));
			player->setTexture(TextureAsset(U"MrJ"));
			player->setGravity(Vec2(0, -0.8f));
		}
		void draw() const {
			player->draw();
		}
		void update() {
			player->update();
		}
	};


}
