#include "PullOutWithNoise.h"
#include "../SpherePart.h"
#include "../../Transform.h"
#include "../../FuturisEngine/Time.h"
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Math/Animation/QuarticOut.h>
#include <Utils/Random.h>

PullOutWithNoise::PullOutWithNoise(float duration, float distance) :
m_duration(duration),
m_distance(distance),
m_time(0.0f)
{
}

PullOutWithNoise::~PullOutWithNoise()
{
}

bool PullOutWithNoise::Update()
{
	m_time = MathUtils::Min(m_duration, m_time + Time::DeltaTime);

	QuarticOut<sm::Vec3> pullOutCurve;
	m_transform->SetLocalPosition(pullOutCurve.Evaluate(m_initialPosition, m_pullOutPosition, m_time / m_duration));

	QuarticOut<sm::Quat> curve;
	m_transform->SetLocalRotation(curve.Evaluate(m_initialRotation, m_destinationRotation, m_time / m_duration));

	return m_time == m_duration;
}

void PullOutWithNoise::SetSpherePart(SpherePart* spherePart)
{
	this->CommandBase::SetSpherePart(spherePart);

	m_initialPosition = m_transform->GetLocalPosition();
	m_pullOutPosition = m_transform->GetLocalPosition() + m_spherePart->m_direction * Random::GetFloat(m_distance * 0.05f, m_distance) + Random::GetVector() * 0.5f;

	m_initialRotation = m_transform->GetLocalRotation();
	m_destinationRotation = sm::Quat::FromAngleAxis(Random::GetFloat(0.1f, 0.3f), Random::GetUniVector());
}

