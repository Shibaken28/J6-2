# include "GameObject.hpp"



namespace MyGame {

	bool hasCommonRange(double l0, double r0, double l1, double r1) {
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
	bool isMovingRectHit(const Rect& rect0, const Point& var0, const Rect& rect1, const Point& var1, bool& isHitX, bool& isHitY, double& hitTime, Point& revert) {
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
		double xt = 100;
		double yt = 100;
		Point v0 = var0 - var1; //相対速度，rect1が停止していると考える
		double fixedX = rect0.x + var0.x;
		double fixedY = rect0.y + var0.y;
		if (v0.x > 0) {

			double x0 = rect0.right().begin.x;
			double t = (rect1.left().begin.x - x0) / v0.x;
			if (0 <= t && t <= 1) {
				Line line0 = rect0.right().movedBy(v0 * t);
				Line line1 = rect1.left();
				if (hasCommonRange(line0.begin.y, line0.end.y, line1.end.y + 1, line1.begin.y - 1)) {
					fixedX = rect1.left().begin.x - rect0.w;// +rect0.h;
					xt = t;
				}
			}
		}
		if (v0.x < 0) {
			double x0 = rect0.left().begin.x;
			double t = (rect1.right().begin.x - x0) / v0.x;
			if (0 <= t && t <= 1) {
				Line line0 = rect0.left().movedBy(v0 * t);
				Line line1 = rect1.right();
				if (hasCommonRange(line0.end.y, line0.begin.y, line1.begin.y + 1, line1.end.y - 1)) {
					fixedX = rect1.right().begin.x;// +rect0.h;
					xt = t;
				}
			}
		}
		if (v0.y < 0) {
			double t = (rect1.bottom().begin.y - rect0.top().begin.y) / v0.y;
			if (0 <= t && t <= 1) {
				Line line0 = rect0.top().movedBy(v0 * t);
				Line line1 = rect1.bottom();
				if (hasCommonRange(line0.begin.x, line0.end.x, line1.end.x + 1, line1.begin.x - 1)) {
					fixedY = rect1.bottom().begin.y;// +rect0.h;
					yt = t;
				}
			}
		}
		if (v0.y > 0) {
			double t = (rect1.top().begin.y - rect0.bottom().begin.y) / v0.y;
			if (0 <= t && t <= 1) {
				Line line0 = rect0.bottom().movedBy(v0 * t);
				Line line1 = rect1.top();
				if (hasCommonRange(line0.begin.x, line0.end.x, line1.begin.x + 1, line1.end.x - 1)) {
					fixedY = rect1.top().begin.y - rect0.h;
					yt = t;
				}
			}
		}
		revert.x = 0;
		revert.y = 0;
		isHitX = false;
		isHitY = false;
		hitTime = 1.0f;
		if (xt > 1 && yt > 1) {
			return false;
		}
		if (xt < yt) {
			isHitX = true;
			hitTime = xt;
			revert.x = fixedX - rect0.x - v0.x;
		}
		if (yt < xt) {
			isHitY = true;
			hitTime = yt;
			revert.y = fixedY - rect0.y - v0.y;
		}

		return true;
	}

	GameObjectHitNode::GameObjectHitNode() {
		objectType = GameObjectType::Player;
	}

	GameObjectHitNode::GameObjectHitNode(GameObjectType type) {
		objectType = type;
	}


}

