#include "AnimationTest.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"

AnimationTest::AnimationTest(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_activeObject(0)
{
}

void AnimationTest::Awake()
{
	m_objects[0] = ScenesManager::GetInstance()->FindGameObject("face1");
	m_objects[1] = ScenesManager::GetInstance()->FindGameObject("face2");
	m_objects[2] = ScenesManager::GetInstance()->FindGameObject("face3");
}

void AnimationTest::Update()
{
	if (Input::GetKeyDown(KeyCode_1))
		m_activeObject = 0;
	if (Input::GetKeyDown(KeyCode_2))
		m_activeObject = 1;
	if (Input::GetKeyDown(KeyCode_3))
		m_activeObject = 2;

	sm::Vec3 position = m_objects[m_activeObject]->Transform.GetLocalPosition();
	sm::Quat rotation = m_objects[m_activeObject]->Transform.GetLocalRotation();

	float moveValue = Time::DeltaTime * 100.0f;
	float angleValue = Time::DeltaTime * 1.0f;

	if (Input::GetKey(KeyCode_T))
		position.y += moveValue;
	if (Input::GetKey(KeyCode_G))
		position.y -= moveValue;
	if (Input::GetKey(KeyCode_F))
		position.x -= moveValue;
	if (Input::GetKey(KeyCode_H))
		position.x += moveValue;

	if (Input::GetKey(KeyCode_R))
		rotation = sm::Quat::FromAngleAxis(angleValue, sm::Vec3(0, 0, 1)) * rotation;

	m_objects[m_activeObject]->Transform.SetLocalPosition(position);
	m_objects[m_activeObject]->Transform.SetLocalRotation(rotation);
}

/*
void AnimationTest::UpdatePosition()
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
*/