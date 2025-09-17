#pragma once
#include <Siv3D.hpp>
#include "config.hpp"
#include "Common.hpp"
#include "../Player/CameraController.hpp"
#include "../Player/Player.hpp"
#include "../Enemy/Enemy.hpp"
#include "../Enemy/Rock.hpp"
#include "../Enemy/BulletEnemy.hpp"
#include "b.hpp"


class Game : public App::Scene
{
public:
	Game(const InitData& init);

	void update() override;
	void draw() const override;
	void Attack();
	void Occurrence();

private:
	MSRenderTexture m_renderTexture;
	DebugCamera3D m_cam;
	CameraController m_cameraController;

	Player m_player;
	Enemy enemy;
	BulletEnemy b_enemy;
	Rock rock;
	Texture m_tex;
	b box;

	void initLighting() const;

	// 現在のゲームスコア
	int32 m_score = 0;

	const Font font{ FontMethod::MSDF, 40 };

	// 敵の発生間隔の初期値（秒）
	static constexpr double InitialEnemySpawnInterval = 4.0;
	// 敵の発生間隔（秒）
	double enemySpawnTime = InitialEnemySpawnInterval;
	// 敵の発生の蓄積時間（秒）
	double enemyAccumulatedTime = 0.0;
};
