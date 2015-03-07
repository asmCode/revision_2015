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

	float moveSpeed = 10.0f;

	if (Input::GetKey(KeyCode_W))
		position.z -= moveSpeed * Time::DeltaTime;

	if (Input::GetKey(KeyCode_S))
		position.z += moveSpeed * Time::DeltaTime;

	m_gameObject->Transform.SetPosition(position);
}
