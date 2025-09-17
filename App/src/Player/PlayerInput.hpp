#pragma once
#include <Siv3D.hpp>

struct PlayerInput
{
	static Vec2 mouseDelta() { return Cursor::DeltaF(); }
	static bool KeyForward() { return KeyN.pressed(); }
	static bool KeyBackward() { return KeyM.pressed(); }
	static bool KeyLeft() { return KeyA.pressed(); }
	static bool KeyRight() { return KeyD.pressed(); }
	static bool KeyUp() { return KeyW.pressed(); }
	static bool KeyDown() { return KeyS.pressed(); }
	static bool KeyShot() { return KeyQ.pressed(); }
};
