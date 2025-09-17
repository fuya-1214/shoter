#include "Enemy.hpp"

Enemy::Enemy()
{
}

void Enemy::Update(double deltatime)
{
	// 進ませる
	for (auto& enemy : enemyPos)
	{
		enemy.z -= (deltatime * EnemySpeed);
	}

	// 通り越したら削除する
	enemyPos.remove_if([](const Vec3& e) {return (e.z < -3);});

}

void Enemy::Draw() const
{
	// モデルに付随するテクスチャをアセット管理に登録
	Model::RegisterDiffuseTextures(em, TextureDesc::MippedSRGB);

	for (const auto& enemy : enemyPos)
	{
		em.draw(enemy, Quaternion::RotateY(90_deg));
	}

}
