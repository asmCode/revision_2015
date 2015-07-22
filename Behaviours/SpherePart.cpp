#include "SpherePart.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../Camera.h"
#include <Math/Animation/QuadOut.h>
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/MathUtils.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"

SpherePart::SpherePart(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_moveOutTime(0.0f),
	m_shiftTime(0.0f)
{
	m_moveOutCurve = new QuadOut<sm::Vec3>();
	m_shiftCurve = new QuadOut<sm::Quat>();

	m_rotatePivot = new GameObject("RotatePivot");
}

void SpherePart::Awake()
{
	m_basePosition = GetGameObject()->GetTransform().GetPosition();
	m_baseRotation = sm::Quat::FromAngleAxis(0.0f, sm::Vec3(1, 0, 0));
	m_moveOutPosition = m_basePosition + m_basePosition.GetNormalized();
	m_shiftRotation = m_baseRotation * sm::Quat::FromAngleAxis(MathUtils::PI, sm::Vec3(1, 0, 0));
}

void SpherePart::Update()
{
	switch (m_state)
	{
	case State_Opening:
		if (m_moveOutTime == 1.0f)
		{
			m_shiftTime += Time::DeltaTime;

			sm::Quat rot = m_shiftCurve->Evaluate(m_baseRotation, m_shiftRotation, m_shiftTime);
			rot.Normalize();
			m_rotatePivot->GetTransform().SetRotation(rot);
		}
		else
		{
			m_moveOutTime += Time::DeltaTime;
			m_moveOutTime = MathUtils::Clamp(m_moveOutTime, 0.0f, 1.0f);

			if (m_moveOutTime == 1.0f)
				GetGameObject()->GetTransform().SetParent(&m_rotatePivot->GetTransform());

			GetGameObject()->GetTransform().SetPosition(m_moveOutCurve->Evaluate(m_basePosition, m_moveOutPosition, m_moveOutTime));
		}
		break;

	default:
		break;
	}
}

void SpherePart::Open()
{
	m_state = State_Opening;
}

