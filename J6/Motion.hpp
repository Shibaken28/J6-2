# pragma once
# include <Siv3D.hpp>

namespace MyGame {
	class Motion {
	protected:
		Vec2 pos;
		Vec2 delta{0,0};
	public:
		Motion();
		Motion(Vec2 v);
		virtual void move() = 0;
		Point getPos();
		Point getDelta();
		virtual void stopX() = 0;
		virtual void stopY() = 0;
		void setPos(Vec2 v);
	};

	class NonMotion : public Motion {
	public:
		NonMotion(Vec2 v);
		void move() override;
		void stopX() override;
		void stopY() override;
	};
	
	class PlayerMotion : public Motion {
	public:
		Input jumpKey, rightKey, leftKey;
		double moveSpeed;
		double jumpPower;
		double fallMaxSpeed;
		Vec2 velocity{0,0};
		int jumpMax;
		Vec2 Gravity;
		PlayerMotion(Vec2 v);
		void move() override;
		void stopX() override;
		void stopY() override;
	};

	class RoundMotion : public Motion {
		Vec2 p1{ 0,0 };
		Vec2 d{ 0,0 };
		double roundTime;
	public:
		RoundMotion(Vec2 p1,Vec2 d, double t);
		void move() override;
		void stopX() override;
		void stopY() override;
	};

}
