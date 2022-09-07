# pragma once
# include <Siv3D.hpp>

namespace MyGame {

	enum class GameObjectType :int16 {
		Player
	};

	struct GameObjectNode {
		GameObjectType objectType;
	};


	class GameObject {
	public:
		bool isAlive;
	public:
		virtual bool isHit(GameObjectNode) = 0;
		virtual void update() = 0;
		virtual GameObjectNode getNode() = 0;
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
		Input keyRight,keyLeft;
		Vec2 prePosition;
		double jumpPower;
		double moveSpeed;
		double resistanceRatio;
	public:
		Player() {
			init();
		}
		void init() {
			jumpMax = 2;
			fallMaxSpeed = 16*60;
			keyJump = KeyZ;
			keyRight = KeyRight;
			keyLeft = KeyLeft;
			jumpPower = 20*60;
			Gravity = Vec2(0.0f, 1.4f*60*60);
			moveSpeed = 10*60;
			resistanceRatio = 0.9f;
		}
		void update() override {
			prePosition = position;
			Vec2 preVelocity = Velocity;
			Velocity += Gravity* Scene::DeltaTime();
			position += (preVelocity + Velocity) * Scene::DeltaTime() / 2;
			if (Velocity.y > fallMaxSpeed)Velocity.y = fallMaxSpeed;
			jump();
			move();
		}
		void jump() {
			if (keyJump.down()) {
				Velocity.y = -jumpPower;
			}
			if (keyJump.up()) {
				if (Velocity.y < 0) {
					Velocity.y /= 2;
				}
			}
			Velocity.x = 0;
		}
		void move() {
			Velocity.x *= resistanceRatio;
			if (keyLeft.pressed()) {
				Velocity.x -= moveSpeed;
			}
			if (keyRight.pressed()) {
				Velocity.x += moveSpeed;
			}
		}
		bool isHit(GameObjectNode node) override {
			return false;
		}
		GameObjectNode getNode() override {
			return GameObjectNode();
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




	class Field : public GameObject{
	protected:
		Vec2 position;
		Size size;
	};

	class Block : public Field {
	private:
		Texture texture;
	public:
		Block() {
			init();
		}
		Block(Vec2 v,Size s) {
			position = v;
			size = s;
			init();
		};
		void init() {
			setTexture(TextureAsset(U"Block"));
		}
		bool isHit(GameObjectNode node) override {
			if (node.objectType == GameObjectType::Player) {

			}
			return false;
		}
		GameObjectNode getNode() override {
			return GameObjectNode();
		}
		void draw() const override {
			Rect(position.asPoint(), size)(texture).draw();
		}
		void update() override {
		}
		void setTexture(Texture t) {
			texture = t;
		}
	};

	class FieldMap {
	private:
		Grid<Field*>* map;
		int16 chipSize ;
	public:
		FieldMap(int h,int w){
			map = new Grid<Field*>(h,w,NULL);
			chipSize = 64;
		}
		void draw() const {
			for (auto y : step(map->height()))
			{
				for (auto x : step(map->width()))
				{
					if ((*map)[y][x] == NULL)continue;
					(*map)[y][x]->draw();
				}
			}
		}
		void update() {
			for (auto y : step(map->height()))
			{
				for (auto x : step(map->width()))
				{
					if ((*map)[y][x] == NULL)continue;
					(*map)[y][x]->update();
				}
			}
		}
		void setBlock(int h,int w) {
			Print << h << w;
			(*map)[h][w] = new Block(Vec2(h* chipSize,w* chipSize),Size(chipSize, chipSize));
		}
	};

}
