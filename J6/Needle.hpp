# pragma once
# include <Siv3D.hpp>
# include "EntityObject.hpp"
# include "Motion.hpp"

namespace MyGame {
	class Needle : public EntityObject {
	private:
		Texture texture;
	public:
		int degree;
		virtual GameObjectHitNode getHitNode() override;
		void hitCheck(const GameObjectHitNode&)override;
		void draw() const override;
		void update() override;
		Needle();
		Needle(Vec2 pos, int deg);
		Needle(Vec2 pos, Size s, int deg);
		void setTexture(Texture t);
		void init();
	};

	class TrollNeedle : public Needle {
	private:
		Texture texture;
		Rect trigger;
	public:
		int degree;
		void hitCheck(const GameObjectHitNode&)override;
		TrollNeedle(Vec2 pos, Size s, int deg, Rect rect,Vec2 vel);
	};
}

