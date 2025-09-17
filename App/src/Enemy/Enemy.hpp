#pragma once
#include <Siv3D.hpp>

class Enemy
{
public:
	Enemy();
	~Enemy() {};
	void Update(double deltatime);
	void Draw() const;
	void Occurrence();

	Array<Vec3> enemyPos = { GenerateEnemy() };
	Vec3 GenerateEnemy()
	{
		return RandomVec3({ -3,3 }, { 0 }, 10);
	}

private:
	// モデルデータをロード
	const Model em{ U"image/enemy/enemy.obj" };

	// 敵のスピード
	static constexpr double EnemySpeed = 1;
};
