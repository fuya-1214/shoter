#pragma once
#include <Siv3D.hpp>
#include "../Core/Config.hpp"
#include "PlayerInput.hpp"

class CameraController
{
public:
	CameraController(BasicCamera3D& cam);
	void Update(double deltaTime);
	void setEye(const Vec3& eye) { m_eye = eye; };
	[[modiscard]] double yaw() const { return m_yaw; }

private:
	BasicCamera3D& m_cam;
	Vec3 m_eye; //カメラの場所
	double m_yaw;
	double m_pitch;
	static constexpr double PitchLimit{ 80_deg };
};

