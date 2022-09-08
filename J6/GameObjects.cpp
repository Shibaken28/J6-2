# pragma once
# include <Siv3D.hpp>


namespace MyGame {


	enum class GameObjectType :int {
		Player,Needle
	};

	using objectShape = std::variant<Triangle>;

	struct GameObjectNode {
		GameObjectType objectType;
		Array<objectShape> shapes;
		GameObjectNode(){}
		GameObjectNode(GameObjectType type) {
			objectType = type;
		}
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


	class CharaObject : public GameObject {
	public:
		Vec2 position{ 0,0 };
		Vec2 Velocity{ 0,0 };
		Size size{ 64,64 };
		Vec2 Center() {
			return position + size / 2;
		}
		Rect rect() {
			return Rect(position.asPoint(),size);
		}

	};

	class Needle : public CharaObject {
	public:
		int degree;
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
			GameObjectNode node(GameObjectType::Needle);
			Vec2 p0 = rect().topCenter() - Center();
			Vec2 p1 = rect().br() - Center();
			Vec2 p2 = rect().bl() - Center();
			p0.rotate(degree * (1_deg));
			p1.rotate(degree * (1_deg));
			p2.rotate(degree * (1_deg));
			p0.moveBy(position+size/2);
			p1.moveBy(position + size / 2);
			p2.moveBy(position + size / 2);
			//Print
			node.shapes.push_back(Triangle(p0, p1, p2));
			return node;
		}
		void draw() const override {
			texture.resized(size).rotated(degree * (1_deg)).draw(position);
		}
		void update() override {
			
		}
		void setTexture(Texture t) {
			texture = t;
		}
	};




	class Player : public CharaObject {
	public:
		int jumpMax;
		Vec2 Gravity;
		Texture texture;
		double fallMaxSpeed;
		Input keyJump;
		Input keyRight,keyLeft;
		Vec2 prePosition;
		double jumpPower;
		double moveSpeed;
		bool deathRequest;
	public:
		Player() {
			init();
		}
		void init() {
			deathRequest = false;
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
			if (deathRequest) {
				death();
			}
			prePosition = position;
			jump();
			horizonMove();
			Velocity += Gravity * Scene::DeltaTime();
			Vec2 preVelocity = Velocity;
			position += (preVelocity + Velocity) * Scene::DeltaTime() / 2;
			position = position.asPoint();
			if (Velocity.y > fallMaxSpeed)Velocity.y = fallMaxSpeed;
		}
		void death(){
			deathRequest = false;
			rect().draw(ColorF(1,0,0));
			//position = Vec2(100,100);
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
		void horizonMove() {
			Velocity.x = 0;
			if (keyLeft.pressed()) {
				Velocity.x -= moveSpeed;
			}
			if (keyRight.pressed()) {
				Velocity.x += moveSpeed;
			}
		}
		bool isHit(GameObjectNode node) override {
			//プレイヤーとnodeの当たり判定
			//針
			if (node.objectType == GameObjectType::Needle) {
				Triangle triangle= std::get<Triangle>(node.shapes[0]);
				if (rect().stretched(-1).intersects(triangle)) {
					deathRequest = true;
				}
			}
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



	/*
	乗れるものなど
	*/
	class Field : public GameObject{
	protected:
		Vec2 position{0,0};
		Vec2 Velocity{0,0};
		Size size{64,64};
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
		int chipSizeInt;
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
			/*
			これは，不十分である
			
			*/
			/*
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
			*/
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

	inline bool hasCommonRange(double l0, double r0, double l1, double r1) {
		if (l0 < l1 && r0 < l1) {
			return false;
		}
		else if (r1 < l0 && r1 < r0) {
			return false;
		}
		else {
			return true;
		}
	}


	inline bool isMovingRectHit(const Rect &rect0,const Vec2 &var0,const Rect &rect1,const Vec2 &var1,bool &isHitX,bool &isHitY,double &hitTime,Vec2 &revert) {
		/*
			1単位時間で
			rect0がvar0，rect1からvar1変化したときに衝突するかどうか，
			またそのときの状況
		*/
		/*
		「進めるところまで進める」のではなく，「戻す」という作業が必要
			動く床を作成したいときに困る．
			動く床がプレイヤーを押すときに，プレイヤー自身は動いていないため，進めるところまで進む方針だと動かない．
			そこで，壁が発生した方向(壁との相対速度)の逆方向側に，めり込まない場所まで押し戻すという処理が必要になる．

			動いている床については基本的に相対速度で考えられるので，
			停止している壁と動いているプレイヤーとの当たり判定が正確にできれば良い
			ここで，x軸とy軸どちらが先に衝突したかも大事である．これにより，どちらの座標を押し戻すべきかがわかる．

			あるオブジェクトXがAからBに移動したときCベクトル=B-Aとする
			全ての重なってはいけないオブジェクトYについて次を調べる
			・ベクトルCのx成分が正ならば，Xの右の辺と，Yの左の辺
			・ベクトルCのx成分が負ならば，Xの左の辺と，Yの右の辺
			・ベクトルCのy成分が正ならば，Xの下の辺と，Yの上の辺
			・ベクトルCのy成分が負ならば，Xの上の辺と，Yの下の辺
			で，Xの辺の軌道上にYが重なっているか，重なった瞬間の時刻tはいくつかを調べる．
			重なっていた場合，それ以上進めないという意味だが，その中でもtが最も小さいところでとまるべきである．
			そのときにどちらの軸に沿った辺であるかによって，速度を0にする
		*/
		double xt = 0;
		double yt = 0;
		Vec2 v0 = var0 - var1; //相対速度，rect1が停止していると考える
		if (v0.x > 0) {
			double x0 = rect0.right().begin.x;
			double t = (rect1.left().begin.x - x0) / v0.x;
			if (0 < t && t < 1) {
				Line line0 = rect0.right().movedBy(v0 * t);
				Line line1 = rect1.left();
				if (hasCommonRange(line0.begin.y,line0.end.y,line1.begin.y,line1.end.y)) {
					xt = t;
				}
			}
		}
		if (v0.x < 0) {
			double x0 = rect0.left().begin.x;
			double t = (rect1.right().begin.x - x0) / v0.x;
			if (0 < t && t < 1) {
				Line line0 = rect0.left().movedBy(v0 * t);
				Line line1 = rect1.right();
				if (hasCommonRange(line0.begin.y, line0.end.y, line1.begin.y, line1.end.y)) {
					xt = t;
				}
			}
		}
		if (v0.y < 0) {
			double y0 = rect0.top().begin.y;
			double t = (rect1.bottom().begin.y - y0) / v0.y;
			if (0 < t && t < 1) {
				Line line0 = rect0.top().movedBy(v0 * t);
				Line line1 = rect1.bottom();
				if (hasCommonRange(line0.begin.x, line0.end.x, line1.begin.x, line1.end.x)) {
					yt = t;
				}
			}
		}
		if (v0.y > 0) {
			double y0 = rect0.bottom().begin.y;
			double t = (rect1.top().begin.y - y0) / v0.y;
			if (0 < t && t < 1) {
				Line line0 = rect0.bottom().movedBy(v0 * t);
				Line line1 = rect1.top();
				if (hasCommonRange(line0.begin.x, line0.end.x, line1.begin.x, line1.end.x)) {
					yt = t;
				}
			}
		}

		isHitX = false;
		isHitY = false;
		hitTime = 1.0f;
		if (xt == 0 && yt == 0) {
			return false;
		}
		if (xt <= yt) {
			isHitX = true;
			hitTime = xt;
		}
		if(yt <= xt) {
			isHitY = true;
			hitTime = yt;
		}
		revert = var0 * (1.0 - hitTime);
		return true;
	}

}

