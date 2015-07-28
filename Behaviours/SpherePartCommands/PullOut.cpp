#include "PullOut.h"
#include "../SpherePart.h"
#include "../../Transform.h"
#include "../../FuturisEngine/Time.h"
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>

PullOut::PullOut(float duration, float distance) :
m_duration(duration),
m_distance(distance),
m_time(0.0f)
{

}

PullOut::~PullOut()
{
}

bool PullOut::Update()
{
	m_time = MathUtils::Min(m_duration, m_time + Time::DeltaTime);

	QuadOut<sm::Vec3> pullOutCurve;

	m_transform->SetLocalPosition(pullOutCurve.Evaluate(m_spherePart->m_basePosition, m_pullOutPosition, m_time / m_duration));

	return m_time == m_duration;
}

void PullOut::SetSpherePart(SpherePart* spherePart)
{
	this->CommandBase::SetSpherePart(spherePart);

	m_pullOutPosition = m_transform->GetLocalPosition() + m_spherePart->m_direction * m_distance;
}

