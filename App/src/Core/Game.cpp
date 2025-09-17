#include "Game.hpp"

Game::Game(const InitData& init)
	: m_renderTexture{Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB}
	, m_cam{m_renderTexture.size(), Config::CamFOV, Config::CamInitialPosition}
	, m_cameraController{m_cam}
	, m_player{}
	, enemy{}
	, b_enemy{}
	, rock{}
	, m_tex{ U"example/texture/uv.png", TextureDesc::MippedSRGB }
	, box{}
	, IScene{init}
{
	initLighting();
}

void Game::initLighting() const
{
	// 光
	Graphics3D::SetGlobalAmbientColor(ColorF{ 0.1 });
	Graphics3D::SetSunColor(ColorF{ 0.1 }); // 平行光
	Graphics3D::SetSunDirection(Vec3{ 0.3, 0.1, 0.2 }.normalized());
}

void Game::update()
{
	const double deltaTime = Scene::DeltaTime();

	m_player.Updeate(deltaTime, m_cameraController.yaw());
	m_player.Step(deltaTime);
	Attack();

	enemy.Update(deltaTime);
	b_enemy.Update(deltaTime);
	rock.Update(deltaTime);

	m_cameraController.setEye(m_player.eye());
	m_cameraController.Update(deltaTime);
	Graphics3D::SetCameraTransform(m_cam);

	enemyAccumulatedTime += deltaTime;
	Occurrence();

	//Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
}

void Game::draw() const
{
	const ColorF bg{ 0.2, 0.5, 0.8 }; // 背景色

	// 3d描画
	{
		const ScopedRenderTarget3D target{ m_renderTexture.clear(bg) };
		//box.draw();
		enemy.Draw();
		b_enemy.Draw();
		rock.Draw();
		m_player.Draw();
		// 床を描画
		//Plane{ 64 }.draw(m_tex);
	}

	// 2d転送
	{
		Graphics3D::Flush();
		m_renderTexture.resolve();
		Shader::LinearToScreen(m_renderTexture);

		// マウスカーソルを非表示にする
		//Cursor::RequestStyle(CursorStyle::Hidden);

		// スコアを描く
		font(m_score).draw( 1260, 16 );
	}

}

void Game::Attack()
{
	// 弾と敵１
	for (auto itEnemy = enemy.enemyPos.begin(); itEnemy != enemy.enemyPos.end();)
	{
		const Box enemyCircle{ *itEnemy, 0.7 };
		bool skip = false;

		for (auto itBullet = m_player.playerBullets.begin(); itBullet != m_player.playerBullets.end();)
		{
			if (enemyCircle.intersects(*itBullet))
			{
				itEnemy = enemy.enemyPos.erase(itEnemy);
				m_player.playerBullets.erase(itBullet);
				skip = true;
				++m_score;
				break;
			}

			++itBullet;
		}

		if (skip)
		{
			continue;
		}

		++itEnemy;
	}

	// 弾と敵２
	for (auto itbEnemy = b_enemy.bEnemyPos.begin(); itbEnemy != b_enemy.bEnemyPos.end();)
	{
		const Box enemyCircle{ *itbEnemy, 0.7 };
		bool skip = false;

		for (auto itBullet = m_player.playerBullets.begin(); itBullet != m_player.playerBullets.end();)
		{
			if (enemyCircle.intersects(*itBullet))
			{
				itbEnemy = b_enemy.bEnemyPos.erase(itbEnemy);
				m_player.playerBullets.erase(itBullet);
				skip = true;
				++m_score;
				break;
			}

			++itBullet;
		}

		if (skip)
		{
			continue;
		}

		++itbEnemy;
	}

	// 弾と岩
	for (auto itRock = rock.rockPos.begin(); itRock != rock.rockPos.end();)
	{
		const Box rockCircle{ *itRock, 0.7 };
		bool skip = false;

		for (auto itBullet = m_player.playerBullets.begin(); itBullet != m_player.playerBullets.end();)
		{
			if (rockCircle.intersects(*itBullet))
			{
				itRock = rock.rockPos.erase(itRock);
				m_player.playerBullets.erase(itBullet);
				skip = true;
				++m_score;
				break;
			}

			++itBullet;
		}

		if (skip)
		{
			continue;
		}

		++itRock;
	}
	bool gameover = false;

	// 自機と敵弾
	for (const auto& enemyBullet : b_enemy.enemyBullets)
	{
		if (enemyBullet.distanceFrom(m_player.playerPos) <= 0.1)
		{
			gameover = true;
			break;
		}
	}

	// 自機と敵１
	for (const auto& enemy : enemy.enemyPos)
	{
		if (enemy.distanceFrom(m_player.playerPos) <= 0.5)
		{
			gameover = true;
			break;
		}
	}

	// 自機と敵２
	for (const auto& b_enemy : b_enemy.bEnemyPos)
	{
		if (b_enemy.distanceFrom(m_player.playerPos) <= 0.5)
		{
			gameover = true;
			break;
		}
	}
	// 自機と岩
	for (const auto& rock : rock.rockPos)
	{
		if (rock.distanceFrom(m_player.playerPos) <= 0.1)
		{
			gameover = true;
			break;
		}
	}
	// ゲームオーバーならリセットする
	if (gameover)
	{
		m_player.playerPos = Vec3{ 0,0,0 };
		m_player.playerBullets.clear();
		enemy.enemyPos.clear();
		b_enemy.bEnemyPos.clear();
		b_enemy.enemyBullets.clear();
		enemySpawnTime = InitialEnemySpawnInterval;
		// スコアシーンへ
		changeScene(State::Score);

		getData().lastScore = m_score;
	}
		
}

void Game::Occurrence()
{
	while (enemySpawnTime <= enemyAccumulatedTime)
	{
		enemyAccumulatedTime -= enemySpawnTime;
		enemySpawnTime = Max(enemySpawnTime * 0.95, 0.3);
		int randomEnemy = Random(0, 2);
		if (randomEnemy == 0)
		{
			enemy.enemyPos << enemy.GenerateEnemy();
		}
		else if (randomEnemy == 1)
		{
			rock.rockPos << rock.GenerateRock();
		}
		else
		{
			b_enemy.bEnemyPos << b_enemy.GeneratebEnemy();
		}
	}

}
