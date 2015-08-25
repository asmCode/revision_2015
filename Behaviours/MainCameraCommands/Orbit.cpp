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
	Orbit::Orbit(MainCamera* mainCamera, float duration, float minAngle, float maxAngle) :
		MainCameraCommandBase(mainCamera),
		m_duration(duration),
		m_minAngle(minAngle),
		m_maxAngle(maxAngle),
		m_time(0.0f)
	{
		m_axis = Random::GetUniVector();
	}

	Orbit::Orbit(MainCamera* mainCamera, float duration, float minAngle, float maxAngle, const sm::Vec3& axis) :
		MainCameraCommandBase(mainCamera),
		m_duration(duration),
		m_minAngle(minAngle),
		m_maxAngle(maxAngle),
		m_axis(axis),
		m_time(0.0f)
	{
	}

	Orbit::~Orbit()
	{
	}

	void Orbit::Enter()
	{
		m_srcRot = m_subject->GetPivotTransform()->GetLocalRotation();
		m_dstRot = sm::Quat::FromAngleAxis(Random::GetFloat(m_minAngle, m_maxAngle), m_axis) * m_srcRot;
	}

	bool Orbit::Update()
	{
		m_time = MathUtils::Min(m_duration, m_time + Time::DeltaTime);

		QuarticOut<sm::Quat> curve;

		m_subject->GetPivotTransform()->SetLocalRotation(curve.Evaluate(m_srcRot, m_dstRot, m_time / m_duration));
		m_subject->GetLookTransform()->GetLocalRotation().LookRotation(m_subject->GetRootTransform()->GetPosition().GetNormalized(), m_subject->GetRootTransform()->GetUp());

		return m_time == m_duration;
	}
}
