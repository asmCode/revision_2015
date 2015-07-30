#include "RollOut.h"
#include "../SpherePart.h"
#include "../../Transform.h"
#include "../../FuturisEngine/Time.h"
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Math/Animation/QuarticOut.h>

RollOut::RollOut(float duration, float angle) :
m_duration(duration),
m_angle(angle),
m_time(0.0f)
{
}

RollOut::~RollOut()
{
}

bool RollOut::Update()
{
	m_time = MathUtils::Min(m_duration, m_time + Time::DeltaTime);

	QuarticOut<sm::Quat> curve;

	m_transform->SetLocalRotation(curve.Evaluate(m_spherePart->m_baseRotation, m_destinationRotation, m_time / m_duration));

	return m_time == m_duration;
}

void RollOut::SetSpherePart(SpherePart* spherePart)
{
	this->CommandBase::SetSpherePart(spherePart);

	m_destinationRotation = sm::Quat::FromAngleAxis(m_angle, m_spherePart->m_direction);
}

