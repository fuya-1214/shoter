#pragma once
#include <Siv3D.hpp>

class Player
{
public:
	Player();
	~Player() {};
	void Updeate(double deltatime, double yaw);
	void BulletUpdate(double deltatime);
	void Draw() const;
	void Step(double deltaTime);

	// 体のもとになる座標からの目の位置のオフセット
	Vec3 eyeOffset{ 0,0.15,0 };
	[[nodiscard]] Vec3 eye() const
	{
		return playerPos + eyeOffset;
	}
	Array<Vec3> playerBullets; // 自機ショット
	Vec3 playerPos{ 0, 0, 0 };  // 初期位置

private:
	// モデルデータをロード
	const Model player{ U"image/player/tt.obj" };
	Vec3 velocity{ 0, 0, 0 }; // 速度


	static constexpr double PlayerBulletSpeed = 2.5; // 弾のスピード
	static constexpr double PlayerShotCoolTime = 0.3; // 自機ショットのクールタイム（秒）
	double playerShotTimer = 0.0; // 自機ショットのクールタイムタイマー（秒）

};

