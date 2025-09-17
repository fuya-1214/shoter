#pragma once
#include <Siv3D.hpp>

class BulletEnemy
{
public:
	BulletEnemy();
	~BulletEnemy() {};
	void Update(double deltatime);
	void Draw() const;
	void Occurrence();

	Array<Vec3> bEnemyPos = { GeneratebEnemy() };
	Vec3 GeneratebEnemy()
	{
		return RandomVec3({ -3,3 }, { 0 }, 10);
	}

	// 敵ショット
	Array<Vec3> enemyBullets;

private:
	// モデルデータをロード
	const Model em{ U"image/bulletEnemy/bulletEnemy.obj" };

	// 敵のスピード
	static constexpr double EnemySpeed = 1;

	// 敵ショットのスピード
	static constexpr double EnemyBulletSpeed = 3.0;

	// 敵ショットのクールタイム（秒）
	static constexpr double EnemyShotCoolTime = 2;
	// 敵ショットのクールタイムタイマー（秒）
	double enemyShotTimer = 0.0;
};
