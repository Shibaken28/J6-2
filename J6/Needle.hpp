# pragma once
# include <Siv3D.hpp>
# include "EntityObject.hpp"

namespace MyGame {
	class Needle : public EntityObject {
	private:
		Texture texture;
	public:
		int degree;
		GameObjectHitNode getHitNode() override;
		void hitCheck(GameObjectHitNode&)override;
		void draw() const override;
		void update() override;
		Needle(Vec2 pos, int deg);
		Needle(Vec2 pos, Size s, int deg);
		void setTexture(Texture t);
		void init();
	};
}

