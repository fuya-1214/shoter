#pragma once
#include <Siv3D.hpp>
#include "Common.hpp"

class Title : public App::Scene
{
public:
	Title(const InitData& init);

	void update() override;

	void draw() const override;

private:
	// 画像ファイルからテクスチャを作成する
	const Texture texture{ U"image/title.png" };

	const Font font{ FontMethod::MSDF, 40 };
};
