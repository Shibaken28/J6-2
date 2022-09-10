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
		virtual void stopX();
		virtual void stopY();
		virtual void reset();
		virtual void onFloor();
		virtual void triggered();
		
		void setPos(Vec2 v);
	};

	class NonMotion : public Motion {
	public:
		NonMotion(Vec2 v);
		void move() override;
	};
	
	class PlayerMotion : public Motion {
	public:
		Input jumpKey, rightKey, leftKey;
		double moveSpeed;
		double jumpPower;
		double fallMaxSpeed;
		Vec2 velocity{0,0};
		int jumpMax ;
		int jumpCount;
		Vec2 Gravity;
		PlayerMotion(Vec2 v);
		void move() override;
		void stopX() override;
		void reset() override;
		void stopY() override;
		void onFloor() override;
	};

	class RoundMotion : public Motion {
		Vec2 p1{ 0,0 };
		Vec2 d{ 0,0 };
		double roundTime;
	public:
		RoundMotion(Vec2 p1,Vec2 d, double t);
		void move() override;
	};


	class TriggerMotion : public Motion {
		Vec2 velocity{ 0,0 };
		bool isTriggered=false;
	public:
		TriggerMotion(Vec2 v,Vec2 ve);
		void move() override;
		void triggered() override;
	};
}
