#include "CameraController.hpp"

CameraController::CameraController(BasicCamera3D& cam)
	: m_cam(cam)
	, m_eye(cam.getEyePosition())
	, m_yaw{ 0.0 }
	, m_pitch{ 0.0 }
{
	const Vec3 dir = (Vec3{ 0,0,0 } - m_eye).normalized(); // 方角調整
	m_yaw = Atan2(dir.z, dir.x);
	m_pitch = Asin(dir.y);
}

void CameraController::Update(double deltaTime)
{
	bool isRightDrag = MouseR.pressed();
	Vec2 mouseDelta = isRightDrag ? PlayerInput::mouseDelta() : Vec2{ 0, 0 };

	if (Abs(mouseDelta.x) < 0.01) mouseDelta.x = 0.0;
	if (Abs(mouseDelta.y) < 0.01) mouseDelta.y = 0.0;

	m_yaw -= mouseDelta.x * Config::CamRotateSpeed;
	m_pitch -= mouseDelta.y * Config::CamRotateSpeed;
	m_pitch = Clamp(m_pitch, -PitchLimit, PitchLimit);

	if (isRightDrag)
	{
		Cursor::RequestStyle(CursorStyle::Hidden);
	}
	else
	{
		Cursor::RequestStyle(CursorStyle::Default);
	}

	const double cp = Cos(m_pitch), sp = Sin(m_pitch);
	const double cy = Cos(m_yaw), sy = Sin(m_yaw);

	const Vec3 forward{ cy * cp, sp, sy * cp };
	const Vec3 right = forward.cross({ 0,1,0 }).normalized();
	const Vec3 up = right.cross(forward).normalized();


	m_cam.setView(m_eye, m_eye + forward, up);
}
