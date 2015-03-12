#include "FppCamera.h"
#include "../GameObject.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"

FppCamera::FppCamera(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_moveSensitivity(1.0f),
	m_rotateSensitivity(1.0f),
	m_angleX(0.0f),
	m_angleY(0.0f),
	m_rotating(0.0f),
	m_lastCursorPos(0, 0)
{
	RegisterParameter("move_sensitivity", &m_moveSensitivity);
	RegisterParameter("rotate_sensitivity", &m_rotateSensitivity);
}

void FppCamera::Update()
{
	UpdatePosition();
	UpdateRotation();

	/*
	GraphicsLog::AddSegment(position, position + forward);
	GraphicsLog::AddSegment(position, position + m_gameObject->Transform.GetForward(), sm::Vec3(0, 0, 1));
	GraphicsLog::AddSegment(position, position + m_gameObject->Transform.GetUp(), sm::Vec3(0, 1, 0));
	GraphicsLog::AddSegment(position, position + m_gameObject->Transform.GetRight(), sm::Vec3(1, 0, 0));
	*/
}

void FppCamera::UpdatePosition()
{
	sm::Vec3 position = m_gameObject->Transform.GetPosition();

	if (Input::GetKey(KeyCode_W))
		position -= m_gameObject->Transform.GetForward() * m_moveSensitivity * Time::DeltaTime;

	if (Input::GetKey(KeyCode_S))
		position += m_gameObject->Transform.GetForward() * m_moveSensitivity * Time::DeltaTime;

	if (Input::GetKey(KeyCode_A))
		position -= m_gameObject->Transform.GetRight() * m_moveSensitivity * Time::DeltaTime;

	if (Input::GetKey(KeyCode_D))
		position += m_gameObject->Transform.GetRight() * m_moveSensitivity * Time::DeltaTime;

	if (Input::GetKey(KeyCode_Q))
		position += sm::Vec3(0, 1, 0) * m_moveSensitivity * Time::DeltaTime;

	if (Input::GetKey(KeyCode_E))
		position -= sm::Vec3(0, 1, 0) * m_moveSensitivity * Time::DeltaTime;

	m_gameObject->Transform.SetPosition(position);
}

void FppCamera::UpdateRotation()
{
	// just clicked
	if (Input::GetKey(KeyCode_Mouse0) && !m_rotating)
	{
		m_rotating = true;
		m_lastCursorPos = Input::GetMousePosition();
		return;
	}

	// just released
	if (!Input::GetKey(KeyCode_Mouse0) && m_rotating)
	{
		m_rotating = false;
		return;
	}

	// during rotation
	if (Input::GetKey(KeyCode_Mouse0) && m_rotating)
	{
		sm::Point<int> currentMousePos = Input::GetMousePosition();
		if (currentMousePos == m_lastCursorPos)
			return;

		m_angleY += (float)(currentMousePos.X - m_lastCursorPos.X) * m_rotateSensitivity;
		m_angleX += (float)(currentMousePos.Y - m_lastCursorPos.Y) * m_rotateSensitivity;

		m_lastCursorPos = Input::GetMousePosition();
	}

	if (!m_rotating)
		return;

	sm::Quat rotation =
		sm::Quat::FromAngleAxis(m_angleY, sm::Vec3(0, 1, 0)) *
		sm::Quat::FromAngleAxis(m_angleX, sm::Vec3(1, 0, 0));

	sm::Vec3 forward = rotation.Rotate(sm::Vec3(0, 0, 1));

	m_gameObject->Transform.SetForward(forward);
}
