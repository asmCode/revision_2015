#include "PullIn.h"
#include "../SpherePart.h"
#include "../../Transform.h"
#include "../../FuturisEngine/Time.h"
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Math/Animation/QuarticOut.h>

PullIn::PullIn(float duration) :
m_duration(duration),
m_time(0.0f)
{

}

PullIn::~PullIn()
{
}

bool PullIn::Update()
{
	m_time = MathUtils::Min(m_duration, m_time + Time::DeltaTime);

	QuarticOut<sm::Vec3> pullOutCurve;
	m_transform->SetLocalPosition(pullOutCurve.Evaluate(m_startPosition, m_spherePart->m_basePosition, m_time / m_duration));

	if (m_startRotation != m_spherePart->m_baseRotation)
	{
		QuarticOut<sm::Quat> curve;
		m_transform->SetLocalRotation(curve.Evaluate(m_startRotation, m_spherePart->m_baseRotation, m_time / m_duration));
	}

	return m_time == m_duration;
}

void PullIn::SetSpherePart(SpherePart* spherePart)
{
	this->CommandBase::SetSpherePart(spherePart);

	m_startPosition = m_transform->GetLocalPosition();
	m_startRotation = m_transform->GetLocalRotation();
}

