#include "FppCamera.h"
#include "../GameObject.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"

FppCamera::FppCamera(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void FppCamera::Update()
{
	sm::Vec3 position = m_gameObject->Transform.GetPosition();
	static float angleY = 0.0f;
	static float angleX = 0.0f;

	float moveSpeed = 1.0f;

	if (Input::GetKey(KeyCode_W))
		position += m_gameObject->Transform.GetForward() * moveSpeed * Time::DeltaTime;

	if (Input::GetKey(KeyCode_S))
		position -= m_gameObject->Transform.GetForward() * moveSpeed * Time::DeltaTime;

	if (Input::GetKey(KeyCode_A))
		position -= m_gameObject->Transform.GetRight() * moveSpeed * Time::DeltaTime;

	if (Input::GetKey(KeyCode_D))
		position += m_gameObject->Transform.GetRight() * moveSpeed * Time::DeltaTime;

	if (Input::GetKey(KeyCode_Q))
		position += sm::Vec3(0, 1, 0) * moveSpeed * Time::DeltaTime;

	if (Input::GetKey(KeyCode_E))
		position -= sm::Vec3(0, 1, 0) * moveSpeed * Time::DeltaTime;

	if (Input::GetKey(KeyCode_Left))
		angleY -= moveSpeed * Time::DeltaTime;

	if (Input::GetKey(KeyCode_Right))
		angleY += moveSpeed * Time::DeltaTime;

	if (Input::GetKey(KeyCode_Up))
		angleX += moveSpeed * Time::DeltaTime;
	if (Input::GetKey(KeyCode_Down))
		angleX -= moveSpeed * Time::DeltaTime;

	m_gameObject->Transform.SetPosition(position);

	sm::Quat rotation =
		sm::Quat::FromAngleAxis(angleY, sm::Vec3(0, 1, 0)) *
		sm::Quat::FromAngleAxis(angleX, sm::Vec3(1, 0, 0));

	sm::Vec3 forward = rotation.Rotate(sm::Vec3(0, 0, 1));

	m_gameObject->Transform.SetForward(forward);

	/*
	GraphicsLog::AddSegment(position, position + forward);
	GraphicsLog::AddSegment(position, position + m_gameObject->Transform.GetForward(), sm::Vec3(0, 0, 1));
	GraphicsLog::AddSegment(position, position + m_gameObject->Transform.GetUp(), sm::Vec3(0, 1, 0));
	GraphicsLog::AddSegment(position, position + m_gameObject->Transform.GetRight(), sm::Vec3(1, 0, 0));
	*/
}
