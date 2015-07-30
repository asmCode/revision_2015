#include "RollIn.h"
#include "../SpherePart.h"
#include "../../Transform.h"
#include "../../FuturisEngine/Time.h"
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Math/Animation/QuarticOut.h>

RollIn::RollIn(float duration) :
m_duration(duration),
m_time(0.0f)
{
}

RollIn::~RollIn()
{
}

bool RollIn::Update()
{
	m_time = MathUtils::Min(m_duration, m_time + Time::DeltaTime);

	QuarticOut<sm::Quat> curve;

	m_transform->SetLocalRotation(curve.Evaluate(m_startRotation, m_spherePart->m_baseRotation, m_time / m_duration));

	return m_time == m_duration;
}

void RollIn::SetSpherePart(SpherePart* spherePart)
{
	this->CommandBase::SetSpherePart(spherePart);

	m_startRotation = m_transform->GetLocalRotation();
}

