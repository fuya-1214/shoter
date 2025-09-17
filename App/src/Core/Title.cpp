#include "Title.hpp"

Title::Title(const InitData& init)
	:IScene{ init }
{
	Font font(30);
}

void Title::update()
{
	if (KeySpace.down())
	{
		changeScene(State::Game);
	}
}

void Title::draw() const
{
	// タイトル画面
	texture.draw(20, 20);

	// テキスト
	font(U"Spaceを押してゲームスタート").drawAt(1280 / 2, 500);

	// マウスカーソルを非表示にする
	//Cursor::RequestStyle(CursorStyle::Hidden);
}
