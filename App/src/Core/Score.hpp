#pragma once
#include <Siv3D.hpp>
#include "Common.hpp"

// スコアシーン
class Score : public App::Scene
{
public:
	Score(const InitData& init);

	void update() override;
	void draw() const override;

private:
	const Font font{ FontMethod::MSDF, 40 };

	int32 score;
};
