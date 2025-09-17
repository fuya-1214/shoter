#pragma once
#include <Siv3D.hpp>

// シーンのステート
enum class State
{
	Title,
	Game,
	Score,
};

// 共有するデータ
struct GameData
{
	// 直前のゲームスコア
	int32 lastScore = 0;
};

using App = SceneManager<State, GameData>;
