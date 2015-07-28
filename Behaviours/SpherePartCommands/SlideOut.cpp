#include "SlideOut.h"
#include "../SpherePart.h"
#include "../../Transform.h"
#include "../../FuturisEngine/Time.h"
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>

SlideOut::SlideOut(float duration, float angle, const sm::Vec3& axis) :
m_duration(duration),
m_angle(angle),
m_axis(axis),
m_time(0.0f)
{

}

SlideOut::~SlideOut()
{
}

bool SlideOut::Update()
{
	m_time = MathUtils::Min(m_duration, m_time + Time::DeltaTime);

	QuadOut<sm::Quat> curve;

	m_pivotTransform->SetLocalRotation(curve.Evaluate(m_baseRotation, m_destinationRotation, m_time / m_duration));

	return m_time == m_duration;
}

void SlideOut::SetSpherePart(SpherePart* spherePart)
{
	this->CommandBase::SetSpherePart(spherePart);

	m_baseRotation = sm::Quat::FromAngleAxis(0.0f, m_axis);
	m_destinationRotation = sm::Quat::FromAngleAxis(m_angle, m_axis);
}

