#pragma once
#include <Siv3D.hpp>

class Rock
{
public:
	Rock();
	~Rock() {};
	void Update(double deltatime);
	void Draw() const;
	void Occurrence();

	Array<Vec3> rockPos = { GenerateRock() };
	Vec3 GenerateRock()
	{
		return RandomVec3({ -3, 3 }, { 0 }, 10);
	}

private:

	// モデルデータをロード
	const Model rock2{ U"image/rock/Rock.obj" };


	// 岩のスピード
	static constexpr double RockSpeed = 1;
};
