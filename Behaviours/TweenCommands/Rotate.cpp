#include "Rotate.h"
#include "../../Transform.h"
#include "../../FuturisEngine/Time.h"
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Math/Animation/QuarticOut.h>
#include <Math/Animation/LinearCurve.h>
#include <Math/Animation/Custom/BlinkCurve.h>
#include <Utils/Random.h>

namespace TweenCommands
{
	Rotate::Rotate(Transform* transform, IAnimationCurve<float>* curve, float duration, float angle, const sm::Vec3& axis) :
		m_transform(transform),
		m_curve(curve),
		m_duration(duration),
		m_angle(angle),
		m_axis(axis),
		m_time(0.0f)
	{
	}

	Rotate::~Rotate()
	{
	}

	void Rotate::Enter()
	{
		m_baseRotation = m_transform->GetLocalRotation();
	}

	bool Rotate::Update()
	{
		m_time = MathUtils::Min(m_duration, m_time + Time::DeltaTime);

		float angle = m_curve->Evaluate(0.0f, m_angle, m_time / m_duration);

		m_transform->SetLocalRotation(sm::Quat::FromAngleAxis(angle, m_axis) * m_baseRotation);

		return m_time == m_duration;
	}
}
