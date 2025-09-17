# include <Siv3D.hpp> // OpenSiv3D v0.6.5
# include <HamFramework.hpp>
# include "App/src/Core/Title.hpp"
# include "App/src/Core/Game.hpp"
# include "App/src/Core/Score.hpp"

void Main()
{
	Window::Resize(1280, 720);

	App manager;
	manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);
	manager.add<Score>(State::Score);

	while (System::Update())
	{
		ClearPrint();

		if (not manager.update())break;

	}
}
