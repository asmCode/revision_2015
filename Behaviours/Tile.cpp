#include "Tile.h"
#include "../GameObject.h"
#include "../Transform.h"
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include <Math/MathUtils.h>
#include <Utils/Random.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"

Tile::Tile(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_velocity(0, 0, 0),
	m_axis(1, 0, 0),
	m_angle(0.0f),
	m_isDetached(false),
	m_baseRotate(0.0f, 1.0f, 0.0f, 0.0f)
{
}

void Tile::Awake()
{
	m_baseRotate = m_gameObject->GetTransform().GetRotation();
}

void Tile::Update()
{
	if (!m_isDetached)
		return;

	float old = Time::DeltaTime;
	//Time::DeltaTime *= 0.1f;


	m_velocity += sm::Vec3(0.0f, -9.8f, 0.0f) * Time::DeltaTime;

	sm::Vec3 position = m_gameObject->GetTransform().GetPosition();
	position += m_velocity * Time::DeltaTime;
	position.y = MathUtils::Max(position.y, 0.0f);
	m_gameObject->GetTransform().SetPosition(position);

	if (position.y == 0)
	{
		m_gameObject->GetTransform().SetRotation(
			sm::Quat::LookRotation(sm::Vec3(1, 0, 0)) *
			sm::Quat::FromAngleAxis(m_angle, sm::Vec3(0, 1, 0)));
		m_velocity -= m_velocity * Time::DeltaTime;
	}
	else
	{
		m_angle += m_spinSpeed * Time::DeltaTime;
		m_gameObject->GetTransform().SetRotation(
			sm::Quat::FromAngleAxis(m_angle, m_axis) *
			m_baseRotate);
	}

	Time::DeltaTime = old;
}

void Tile::Blow()
{
	m_isDetached = true;
	m_velocity = (Random::GetVector() + m_gameObject->GetTransform().GetUp() * 2.0f) * Random::GetFloat(1.0f, 5.0f);

	m_axis = Random::GetUniVector();
	m_spinSpeed = Random::GetFloat(0.2f, 10.0f);
}

bool Tile::IsDetached() const
{
	return m_isDetached;
}

