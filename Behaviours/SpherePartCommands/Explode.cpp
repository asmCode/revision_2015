#include "Explode.h"
#include "../SpherePart.h"
#include "../../Transform.h"
#include "../../FuturisEngine/Time.h"
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Math/Animation/QuarticOut.h>
#include <Utils/Random.h>

Explode::Explode()
{
}

Explode::~Explode()
{
}

bool Explode::Update()
{
	m_velocity += sm::Vec3(0.0f, -9.8f, 0.0f) * Time::DeltaTime;

	sm::Vec3 position = m_transform->GetPosition();
	position += m_velocity * Time::DeltaTime;
	m_transform->SetPosition(position);

	m_angle += m_spinSpeed * Time::DeltaTime;
	m_transform->SetRotation(
		sm::Quat::FromAngleAxis(m_angle, m_axis) *
		m_startRotation);

	m_spinSpeed -= Time::DeltaTime * 0.1f;
	m_spinSpeed = MathUtils::Max(m_spinSpeed, 0.0f);

	return false;
}

void Explode::SetSpherePart(SpherePart* spherePart)
{
	this->SphereCommandBase::SetSpherePart(spherePart);

	m_startRotation = m_transform->GetLocalRotation();
	
	m_angle = 0.0f;

	//m_velocity = (Random::GetVector() + m_spherePart->GetDirection() * 5.0f) * Random::GetFloat(2.0f, 10.0f);
	m_velocity = sm::Vec3(0, 0, -1) * Random::GetFloat(5.0f, 20.0f);
	m_velocity += m_spherePart->GetDirection() * Random::GetFloat(5.0f, 20.0f);
	m_velocity += Random::GetVector() * Random::GetFloat(2.0f, 4.0f);

	m_axis = Random::GetUniVector();
	m_spinSpeed = Random::GetFloat(0.2f, 6.0f);
}

