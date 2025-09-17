#include "Rock.hpp"

Rock::Rock()
{
}

void Rock::Update(double deltatime)
{
	// 進ませる
	for (auto& rock : rockPos)
	{
		rock.z -= (deltatime * RockSpeed);
	}

	// 通り越したら削除する
	rockPos.remove_if([](const Vec3& e) {return (e.z < -3); });

}

void Rock::Draw() const
{
	// モデルに付随するテクスチャをアセット管理に登録
	Model::RegisterDiffuseTextures(rock2, TextureDesc::MippedSRGB);

	for (const auto& rock : rockPos)
	{
		rock2.draw(rock, Quaternion::RotateZ(Scene::Time() * 30_deg) * Quaternion::RotateX(Scene::Time() * 30_deg));
	}
}
