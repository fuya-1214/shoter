#include "Player.hpp"
#include "PlayerInput.hpp"
#include "../Core/config.hpp"

Player::Player()
{ }

void Player::Updeate(double deltatime, double yaw)
{
	Vec3 forward{ Cos(yaw), 0.0, Sin(yaw) };
	Vec3 right{ -Sin(yaw), 0.0, Cos(yaw) };

	Vec3 move{};
//	if (PlayerInput::KeyForward()) move += forward;
//	if (PlayerInput::KeyBackward()) move -= forward;
	if (PlayerInput::KeyUp()) playerPos.y += 0.01;
	if (PlayerInput::KeyDown()) playerPos.y += -0.01;
	if (PlayerInput::KeyLeft()) move += right;
	if (PlayerInput::KeyRight()) move -= right;

	if (move.lengthSq() > 0.0)
	{
		Vec3 dir = move.normalized() * Config::CamMoveSpeed;
		 velocity.x = dir.x;
		 velocity.z = dir.z;
	}
	else
	{
		velocity.x = 0;
		velocity.z = 0;
	}

	if (playerPos.x <= -5) { playerPos.x = -5; }
	if (playerPos.x >= 5) { playerPos.x = 5; }
	if (playerPos.z <= -5) { playerPos.z = -5; }
	if (playerPos.z >= 5) { playerPos.z = 5; }

	BulletUpdate(deltatime);
}

void Player::BulletUpdate(double deltatime)
{
	playerShotTimer = Min((playerShotTimer + deltatime), PlayerShotCoolTime);

	// 弾を出す
	if (PlayerShotCoolTime <= playerShotTimer)
	{
		if (MouseL.down())
		{
			playerShotTimer -= PlayerShotCoolTime;
			playerBullets << playerPos.movedBy(0, -0.5, 1.7);
		}
	}

	// 自機ショットを移動させる
	for (auto& playerBullet : playerBullets)
	{
		playerBullet.z += (deltatime * +PlayerBulletSpeed);

	}
		
	// 自機ショットを削除する
	playerBullets.remove_if([](const Vec3& b) { return (b.z > 30); });
}

void Player::Draw() const
{
	// モデルに付随するテクスチャをアセット管理に登録
	Model::RegisterDiffuseTextures(player, TextureDesc::MippedSRGB);

	player.draw(playerPos);
	// スコープ代わり
	Box{ playerPos.x, playerPos.y, playerPos.z + 1, 0.03 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());

	// 弾の描画
	for (auto& playerBullet : playerBullets)
	{
		Sphere{ playerBullet, 0.1 }.draw(Palette::Orange);
	}
}

void Player::Step(double deltaTime)
{
	playerPos += velocity * deltaTime;
}
