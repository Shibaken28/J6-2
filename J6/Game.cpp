# include "Game.hpp"

Game::Game(const InitData& init)
	: IScene{ init }
{
	// 横 (Scene::Width() / blockSize.x) 個、縦 5 個のブロックを配列に追加する
	for (auto p : step(Size{ (Scene::Width() / BrickSize.x), 5 }))
	{
		m_bricks << Rect{ (p.x * BrickSize.x), (60 + p.y * BrickSize.y), BrickSize };
	}
}

void Game::update()
{
	// ボールを移動
	m_ball.moveBy(m_ballVelocity * Scene::DeltaTime());

	// ブロックを順にチェック
	for (auto it = m_bricks.begin(); it != m_bricks.end(); ++it)
	{
		// ブロックとボールが交差していたら
		if (it->intersects(m_ball))
		{
			// ボールの向きを反転する
			(it->bottom().intersects(m_ball) || it->top().intersects(m_ball)
				? m_ballVelocity.y : m_ballVelocity.x) *= -1;

			// ブロックを配列から削除（イテレータが無効になるので注意）
			m_bricks.erase(it);

			AudioAsset(U"Brick").playOneShot(0.5);

			// スコアを加算
			++m_score;

			// これ以上チェックしない
			break;
		}
	}

	// 天井にぶつかったらはね返る
	if (m_ball.y < 0 && m_ballVelocity.y < 0)
	{
		m_ballVelocity.y *= -1;
	}

	// 左右の壁にぶつかったらはね返る
	if ((m_ball.x < 0 && m_ballVelocity.x < 0)
		|| (Scene::Width() < m_ball.x && 0 < m_ballVelocity.x))
	{
		m_ballVelocity.x *= -1;
	}

	// パドルにあたったらはね返る
	if (const Rect paddle = getPaddle();
		(0 < m_ballVelocity.y) && paddle.intersects(m_ball))
	{
		// パドルの中心からの距離に応じてはね返る方向を変える
		m_ballVelocity = Vec2{ (m_ball.x - paddle.center().x) * 10, -m_ballVelocity.y }.setLength(Speed);
	}

	// 画面外に出るか、ブロックが無くなったら
	if ((Scene::Height() < m_ball.y) || m_bricks.isEmpty())
	{
		// ランキング画面へ
		changeScene(State::Ranking);

		getData().lastGameScore = m_score;
	}
}

void Game::draw() const
{
	Scene::SetBackground(ColorF{ 0.2 });

	// すべてのブロックを描画する
	for (const auto& brick : m_bricks)
	{
		brick.stretched(-1).draw(HSV{ brick.y - 40 });
	}

	// ボールを描く
	m_ball.draw();

	// パドルを描く
	getPaddle().draw();

	FontAsset(U"GameScore")(m_score).draw(10, 10);
}

Rect Game::getPaddle() const
{
	return{ Arg::center(Cursor::Pos().x, 500), 60, 10 };
}
