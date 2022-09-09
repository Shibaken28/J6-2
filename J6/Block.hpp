# pragma once
# include <Siv3D.hpp>
# include "EntityObject.hpp"


namespace MyGame {
	class Block : public EntityObject {
	private:
		Texture texture;
	public:
		Block();
		Block(Vec2 , Size, int);
		GameObjectHitNode getHitNode() override;
		void hitCheck(GameObjectHitNode&)override ;
		void draw() const override;
		void update() override;
		void setTexture(Texture t);
		void init();
	};
}

