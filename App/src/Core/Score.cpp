#include "Score.hpp"

Score::Score(const InitData& init)
	: IScene{init}
{
}

void Score::update()
{
	if (KeySpace.down())
	{
		// タイトル画面へ
		changeScene(State::Title);
	}

}

void Score::draw() const
{
	Scene::SetBackground(ColorF{ 0.4, 0.6, 0.9 });
	const auto& data = getData();

	font(data.lastScore).drawAt(715, 720 / 2);

	font(U"Score").drawAt(1280 / 2, 720 / 2);
}
