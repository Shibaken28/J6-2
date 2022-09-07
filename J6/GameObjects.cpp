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

	class DynamicObject : public GameObject {
	public:
		Vec2 position{ 0,0 };
		Vec2 Velocity{ 0,0 };
		Size size{ 64,64 };

	};

	class Needle : public DynamicObject {
	public:
		int16 degree;
		Texture texture;
		Needle(Vec2 pos, int deg) {
			position = pos;
			degree = deg;
			init();
		}
		Needle(Vec2 pos,Size s, int deg) {
			position = pos;
			degree = deg;
			size = s;
			init();
		}
		void init() {
			setTexture(TextureAsset(U"Needle"));
		}
		bool isHit(GameObjectNode node) override {
			return false;
		}
		GameObjectNode getNode() override {
			return GameObjectNode();
		}
		void draw() const override {
			Print << degree;
			texture.resized(size).rotated(degree * (1_deg)).draw(position);
		}
		void update() override {
			
		}
		void setTexture(Texture t) {
			texture = t;
		}
	};




	class Player : public DynamicObject {
	public:
		int16 jumpMax;
		Vec2 Gravity;
		Texture texture;
		double fallMaxSpeed;
		Input keyJump;
		Input keyRight,keyLeft;
		Vec2 prePosition;
		double jumpPower;
		double moveSpeed;
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
			jumpPower = 17*60;
			Gravity = Vec2(0.0f, 1.0f*60*60);
			moveSpeed = 6*60;
		}
		void update() override {
			prePosition = position;
			jump();
			move();
			Velocity += Gravity * Scene::DeltaTime();
			Vec2 preVelocity = Velocity;
			position += (preVelocity + Velocity) * Scene::DeltaTime() / 2;
			position = position.asPoint();
			if (Velocity.y > fallMaxSpeed)Velocity.y = fallMaxSpeed;
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
		}
		void move() {
			Velocity.x = 0;
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
		Vec2 getPrePosition() {
			return prePosition;
		}
		Size getSize() {
			return size;
		}
		void setTexture(Texture t) {
			texture = t;
		}
		Vec2 deltaPos() {
			return position - prePosition;
		}
	};




	class Field : public GameObject{
	protected:
		Vec2 position;
		Size size;
	public:
		virtual bool isWall() = 0;
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
		bool isWall() override{
			return true;
		}
	};

	class FieldMap {
	private:
		Grid<Field*>* map;
		Size chipSize;
		int16 chipSizeInt;
	public:
		FieldMap(int h,int w){
			map = new Grid<Field*>(h,w,NULL);
			chipSize = Size(64,64);
			chipSizeInt = 64;
		}
		bool isInRange(Point p) {
			return 0 <= p.x && 0 <= p.y && p.x < map->width() && p.y < map->height();
		}
		void wallResistance(Player& player) {
			auto delta = player.deltaPos().asPoint();
			auto beginPos = player.getPrePosition().asPoint();
			auto beginChip = beginPos / chipSize;
			//移動先のチップ座標
			auto fixed = player.getPrePosition().asPoint();

			int dx = (delta.x>0?1:-1);
			bool isCollisionX = false;
			for (int x = 0; Abs(x) <= Abs(delta.x); x += dx) {
				if (delta.x == 0)break;
				fixed.moveBy(dx, 0);
				Rect playerRect(fixed, player.getSize());
				for (auto dcy : Range(-1, 1, 1)) {
					for (auto dcx : Range(-1, 1, 1)) {
						Point pos = beginChip + Point(dcx, dcy);
						Rect chipRect(pos * chipSizeInt, chipSize);
						if (not isInRange(pos))continue;
						if ((*map)[pos.y][pos.x] == NULL)continue;
						if (not (*map)[pos.y][pos.x]->isWall())continue;
						if (chipRect.intersects(playerRect)) {
							isCollisionX = true;
							fixed.moveBy(-dx, 0);
							break;
						}
					}
					if (isCollisionX)break;
				}
				if (isCollisionX)break;
			}
			if (isCollisionX) {
				player.Velocity.x = 0;
			}

			int dy =(delta.y>0?1:-1);
			bool isCollisionY = false;
			for (int y = 0; Abs(y) <= Abs(delta.y); y += dy) {
				if (delta.y == 0)break;
				fixed.moveBy(0, dy);
				Rect playerRect(fixed, player.getSize());
				for (auto dcy : Range(-1, 1, 1)) {
					for (auto dcx : Range(-1, 1, 1)) {
						Point pos = beginChip + Point(dcx, dcy);
						Rect chipRect(pos * chipSizeInt, chipSize);
						if (not isInRange(pos))continue;
						if ((*map)[pos.y][pos.x] == NULL)continue;
						if (not (*map)[pos.y][pos.x]->isWall())continue;
						if (chipRect.intersects(playerRect)) {
							isCollisionY = true;
							fixed.moveBy(0, -dy);
							break;
						}
					}
					if (isCollisionY)break;
				}
				if (isCollisionY)break;
			}
			if (isCollisionY) {
				player.Velocity.y = 0;
			}
			Print << fixed;
			player.position = fixed;
		}
		
		bool isInWall(Vec2 v) {
			Point check = (v.asPoint() / chipSizeInt);
			if (check.x < 0 || check.x >= map->width() || check.y<0 || check.y>map->height()) {
				return false;
			}
			return (*map)[check.y][check.x] != NULL;
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
			(*map)[h][w] = new Block(Vec2(w* chipSizeInt,h* chipSizeInt), chipSize);
		}
	};

}



