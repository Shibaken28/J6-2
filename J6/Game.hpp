# pragma once
# include "Common.hpp"

// ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;

private:

	// ブロックのサイズ
	static constexpr Size BrickSize{ 40, 20 };

	// ボールの速さ
	static constexpr double Speed = 480.0;

	// ボールの速度
	Vec2 m_ballVelocity{ 0, -Speed };

	// ボール
	Circle m_ball{ 400, 400, 8 };

	// ブロックの配列
	Array<Rect> m_bricks;

	// 現在のゲームのスコア
	int32 m_score = 0;

	Rect getPaddle() const;
};
