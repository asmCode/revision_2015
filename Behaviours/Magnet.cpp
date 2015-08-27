#include "Magnet.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../GraphicsLog.h"
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include <Math/MathUtils.h>
#include <Utils/Random.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"

Magnet::Magnet(GameObject* gameObject, const std::string& name) :
Behaviour(gameObject, name),
//m_xAngle(Random::GetFloat(0.0f, MathUtils::PI * 2.0f)),
//m_xAngleSpeed(Random::GetFloat(0.4f, MathUtils::PI * 0.8f)),
//m_yAngle(Random::GetFloat(0.0f, MathUtils::PI * 2.0f)),
//m_yAngleSpeed(Random::GetFloat(0.2f, MathUtils::PI * 0.5f)),
//m_zAngle(Random::GetFloat(0.0f, MathUtils::PI * 2.0f)),
//m_zAngleSpeed(Random::GetFloat(0.5f, MathUtils::PI * 1.0f)),
m_xAngle(Random::GetFloat(0.0f, MathUtils::PI * 2.0f)),
m_xAngleSpeed(Random::GetFloat(0.2f, 0.4f)),
m_yAngle(Random::GetFloat(1.0f, MathUtils::PI * 2.0f)),
m_yAngleSpeed(Random::GetFloat(2.0f, 2.0f)),
m_zAngle(Random::GetFloat(0.0f, 0)),
m_zAngleSpeed(Random::GetFloat(0.0f, 0)),
m_pivot(nullptr)
{
}

void Magnet::Initialize(Transform* parent)
{
	m_pivot = new GameObject("Magnet");
	m_pivot->GetTransform().SetParent(parent);
	m_pivot->GetTransform().SetLocalPosition(sm::Vec3(0, 0, 0));
	m_pivot->GetTransform().SetLocalRotation(sm::Quat(1, 0, 0, 0));
	GetGameObject()->GetTransform().SetParent(&m_pivot->GetTransform());
	GetGameObject()->GetTransform().SetLocalPosition(sm::Vec3(20, 0, 0));
	GetGameObject()->GetTransform().SetLocalRotation(sm::Quat(1, 0, 0, 0));
}

void Magnet::Awake()
{
}

void Magnet::Update()
{
	m_pivot->GetTransform().SetLocalRotation(
		sm::Quat::FromAngleAxis(m_xAngle, sm::Vec3(1, 0, 0)) *
		sm::Quat::FromAngleAxis(m_yAngle, sm::Vec3(0, 1, 0)) *
		sm::Quat::FromAngleAxis(m_zAngle, sm::Vec3(0, 0, 1)));

	m_xAngle += Time::DeltaTime * m_xAngleSpeed;
	m_yAngle += Time::DeltaTime * m_yAngleSpeed;
	m_zAngle += Time::DeltaTime * m_zAngleSpeed;

	sm::Vec3 position = GetGameObject()->GetTransform().GetPosition();

	/*
	GraphicsLog::AddSegment(position, position + sm::Vec3(0, 0.1f, 0));
	GraphicsLog::AddSegment(position, position + sm::Vec3(0, 0.0f, 0.1f));
	GraphicsLog::AddSegment(position, position + sm::Vec3(0.1f, 0.0f, 0));
	*/
}
