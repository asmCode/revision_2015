#include "CameraPivot.h"
#include "../GameObject.h"
#include "../Transform.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"

CameraPivot::CameraPivot(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_speed(1.0f),
	m_angle(0.0f)
{
	RegisterParameter("speed", &m_speed);

	m_baseRotation = m_gameObject->GetTransform().GetRotation();
}

void CameraPivot::Update()
{
	m_angle -= Time::DeltaTime * m_speed;

	m_gameObject->GetTransform().SetRotation(
		sm::Quat::FromAngleAxis(m_angle, sm::Vec3(0, 1, 0)) *
		m_baseRotation);
}
