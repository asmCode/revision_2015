#include "SlideIn.h"
#include "../SpherePart.h"
#include "../../Transform.h"
#include "../../FuturisEngine/Time.h"
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>

SlideIn::SlideIn(float duration) :
m_duration(duration),
m_time(0.0f)
{

}

SlideIn::~SlideIn()
{
}

bool SlideIn::Update()
{
	m_time = MathUtils::Min(m_duration, m_time + Time::DeltaTime);

	QuadOut<sm::Quat> curve;

	m_pivotTransform->SetLocalRotation(curve.Evaluate(m_startRotation, m_spherePart->m_basePivotRotation, m_time / m_duration));

	return m_time == m_duration;
}

void SlideIn::SetSpherePart(SpherePart* spherePart)
{
	this->SphereCommandBase::SetSpherePart(spherePart);

	m_startRotation = m_pivotTransform->GetLocalRotation();
}

