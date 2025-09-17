#include "BulletEnemy.hpp"

BulletEnemy::BulletEnemy()
{
}

void BulletEnemy::Update(double deltatime)
{
	// 進ませる
	for (auto& enemy : bEnemyPos)
	{
		enemy.z -= (deltatime * EnemySpeed);
	}

	// 通り越したら削除する
	bEnemyPos.remove_if([](const Vec3& e) {return (e.z < -3); });

	enemyShotTimer += deltatime;

	// 敵ショットの発射
	if (EnemyShotCoolTime <= enemyShotTimer)
	{
		enemyShotTimer -= EnemyShotCoolTime;

		for (const auto& enemy : bEnemyPos)
		{
			enemyBullets << enemy;
		}
	}

	// 敵ショットを移動させる
	for (auto& enemyBullet : enemyBullets)
	{
		enemyBullet.z -= (deltatime * EnemyBulletSpeed);
	}
	// 画面外に出た敵ショットを削除する
	enemyBullets.remove_if([](const Vec3& b) {return (0 > b.z); });
}

void BulletEnemy::Draw() const
{
	// モデルに付随するテクスチャをアセット管理に登録
	Model::RegisterDiffuseTextures(em, TextureDesc::MippedSRGB);

	for (const auto& enemy : bEnemyPos)
	{
		em.draw(enemy, Quaternion::RotateY(90_deg));
	}

	// 敵ショットを描画
	for (const auto& enemyBullet : enemyBullets)
	{
		Sphere{ enemyBullet, 0.1 }.draw(Palette::Red);
	}
}

