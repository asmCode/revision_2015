#include "SmoothNoise.h"
#include "../DemoUtils.h"
#include "../Transform.h"
#include "../FuturisEngine/Time.h"
#include <Utils/Random.h>

SmoothNoise::SmoothNoise(GameObject* gameObject, const std::string& name) :
Behaviour(gameObject, name),
m_posTime(0.0f),
m_rotTime(0.0f),
m_posSpeed(0.0f),
m_rotSpeed(0.0f)
{
}

void SmoothNoise::Update()
{
	if (m_posSpeed > 0.0f)
	{
		m_posTime += Time::DeltaTime;

		float posTime = m_posTime * m_posSpeed;
		posTime = fmodf(posTime, m_posCurve.GetEndTime());

		sm::Vec3 pos = m_posCurve.Evaluate(posTime);
		GetGameObject()->GetTransform().SetLocalPosition(pos);
	}

	if (m_rotSpeed > 0.0f)
	{
		m_rotTime += Time::DeltaTime;

		float rotTime = m_rotTime * m_rotSpeed;
		rotTime = fmodf(rotTime, m_rotCurve.GetEndTime());

		sm::Quat rot = m_rotCurve.Evaluate(rotTime).GetNormalized();
		GetGameObject()->GetTransform().SetLocalRotation(rot);
	}
}

void SmoothNoise::TranslationNoise(float speed, float range)
{
	m_posTime = 0.0f;

	m_posCurve.Clear();

	float time = 0.0f;
	m_posCurve.AddKeyframe(time, GetGameObject()->GetTransform().GetLocalPosition());
	time += 1.0f;
	for (size_t i = 0; i < 30; i++)
	{
		m_posCurve.AddKeyframe(time, Random::GetUniVector() * range);
		time += 1.0f;
	}
	m_posCurve.AddKeyframe(time, m_posCurve.GetKeyframe(0).Value);
	m_posCurve.SmoothTangents();

	m_posSpeed = speed;
}

void SmoothNoise::RotationNoise(float speed, float angle)
{
	m_rotTime = 0.0f;

	m_rotCurve.Clear();

	float time = 0.0f;
	m_rotCurve.AddKeyframe(time, GetGameObject()->GetTransform().GetLocalRotation());
	time += 1.0f;
	for (size_t i = 0; i < 30; i++)
	{
		m_rotCurve.AddKeyframe(time, sm::Quat::FromAngleAxis(angle, Random::GetUniVector()));
		time += 1.0f;
	}
	m_rotCurve.AddKeyframe(time, m_rotCurve.GetKeyframe(0).Value);
	m_rotCurve.SmoothTangents();

	m_rotSpeed = speed;
}
