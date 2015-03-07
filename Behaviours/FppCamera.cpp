#include "FppCamera.h"
#include "../GameObject.h"
#include <UserInput/Input.h>
#include "../FuturisEngine/Time.h"

FppCamera::FppCamera(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void FppCamera::Update()
{
	sm::Vec3 position = m_gameObject->Transform.GetPosition();

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
		position += m_gameObject->Transform.GetUp() * moveSpeed * Time::DeltaTime;

	if (Input::GetKey(KeyCode_E))
		position -= m_gameObject->Transform.GetUp() * moveSpeed * Time::DeltaTime;

	m_gameObject->Transform.SetPosition(position);
}
