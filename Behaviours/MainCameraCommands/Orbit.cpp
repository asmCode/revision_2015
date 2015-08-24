#include "Orbit.h"
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
	Orbit::Orbit(float duration, float maxAngle) :
		m_duration(duration),
		m_maxAngle(maxAngle),
		m_time(0.0f)
	{

	}

	Orbit::~Orbit()
	{
	}

	void Orbit::Enter()
	{
		m_srcRot = m_subject->GetPivotTransform()->GetLocalRotation();
		m_dstRot = sm::Quat::FromAngleAxis(Random::GetFloat(0.5f, m_maxAngle), Random::GetUniVector()) * m_srcRot;
	}

	bool Orbit::Update()
	{
		m_time = MathUtils::Min(m_duration, m_time + Time::DeltaTime);

		QuarticOut<sm::Quat> curve;

		m_subject->GetPivotTransform()->SetLocalRotation(curve.Evaluate(m_srcRot, m_dstRot, m_time / m_duration));
		m_subject->GetLookTransform()->SetForward(m_subject->GetRootTransform()->GetPosition().GetNormalized());

		return m_time == m_duration;
	}
}
