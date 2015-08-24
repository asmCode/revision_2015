#include "Roll.h"
#include "../../Transform.h"
#include "../../FuturisEngine/Time.h"
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Math/Animation/QuarticOut.h>
#include <Math/Animation/LinearCurve.h>
#include <Math/Animation/Custom/BlinkCurve.h>
#include <Utils/Random.h>

namespace MainCameraCommands
{
	Roll::Roll(float duration, float minAngle, float maxAngle) :
		m_duration(duration),
		m_minAngle(minAngle),
		m_maxAngle(maxAngle),
		m_time(0.0f)
	{
	}

	Roll::~Roll()
	{
	}

	void Roll::Enter()
	{
		m_srcRot = m_subject->GetLookTransform()->GetLocalRotation();
		m_dstRot = sm::Quat::FromAngleAxis(Random::GetFloat(m_minAngle, m_maxAngle), sm::Vec3(0, 0, 1)) * m_srcRot;
	}

	bool Roll::Update()
	{
		m_time = MathUtils::Min(m_duration, m_time + Time::DeltaTime);

		QuarticOut<sm::Quat> curve;

		m_subject->GetLookTransform()->SetLocalRotation(curve.Evaluate(m_srcRot, m_dstRot, m_time / m_duration));

		return m_time == m_duration;
	}
}
