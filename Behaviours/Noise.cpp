#include "Noise.h"
#include "../DemoUtils.h"
#include "../Transform.h"
#include "../FuturisEngine/Time.h"
#include <Utils/Random.h>

Noise::Noise(GameObject* gameObject, const std::string& name) :
Behaviour(gameObject, name),
m_translationSpeed(0.0f),
m_translationRange(0.0f),
m_rotationSpeed(0.0f),
m_rotationAngle(0.0f),
m_translateFrom(sm::Vec3(0, 0, 0)),
m_translateTo(sm::Vec3(0, 0, 0)),
m_translateTime(0.0f),
m_rotateFrom(sm::Quat(1, 0, 0, 0)),
m_rotateTo(sm::Quat(1, 0, 0, 0)),
m_rotateTime(0.0f)
{
}

void Noise::Update()
{
	if (m_translationSpeed != 0.0f)
	{
		if (DemoUtils::StepTo(m_translateFrom, m_translateTo, m_translationSpeed * Time::DeltaTime))
		{
			m_translateFrom = m_translateTo;
			m_translateTo = GetNextTranslation();
		}

		GetGameObject()->GetTransform().SetLocalPosition(m_translateFrom);
	}

	if (m_rotationSpeed != 0.0f)
	{
		if (DemoUtils::StepTo(m_rotateFrom, m_rotateTo, m_rotationSpeed * Time::DeltaTime))
		{
			m_rotateFrom = m_rotateTo;
			GetNextRotation();
		}

		GetGameObject()->GetTransform().SetLocalRotation(m_rotateFrom);
	}
}

void Noise::TranslationNoise(float speed, float range)
{
	m_translationRange = range;

	if (m_translationSpeed == 0.0f)
	{
		m_translateTo = GetNextTranslation();
	}

	m_translationSpeed = speed;
}

void Noise::RotationNoise(float speed, float angle)
{
	m_rotationAngle = angle;

	if (m_rotationSpeed == 0.0f)
	{
		GetNextRotation();
	}

	m_rotationSpeed = speed;
}

sm::Vec3 Noise::GetNextTranslation()
{
	return Random::GetUniVector() * m_translationRange;
}

void Noise::GetNextRotation()
{
	m_rotateTo = sm::Quat::FromAngleAxis(m_rotationAngle, Random::GetUniVector());
}

