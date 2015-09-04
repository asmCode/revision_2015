#include "MechArm.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../GraphicsLog.h"
#include "../FuturisEngine/Time.h"
#include <UserInput\Input.h>
#include <Math/MathUtils.h>

MechArm::MechArm(GameObject* gameObject, const std::string& name) :
Behaviour(gameObject, name),
m_target(0, 0, 0)
{
}

sm::Vec3 endPos;

void MechArm::Awake()
{
	m_base = &GetGameObject()->GetTransform();
	m_arm1 = &GetGameObject()->FindChild("Arm1", true)->GetTransform();
	m_arm2 = &GetGameObject()->FindChild("Arm2", true)->GetTransform();
	m_end = &GetGameObject()->FindChild("End", true)->GetTransform();

	m_arm1Length = (m_arm2->GetPosition() - m_arm1->GetPosition()).GetLength();
	m_arm2Length = (m_end->GetPosition() - m_arm2->GetPosition()).GetLength();

	endPos = m_end->GetPosition();
}

void MechArm::SetTarget(const sm::Vec3& target)
{
	m_target = target;
}

void MechArm::Update()
{
	float moveValue = 1.0f * Time::DeltaTime;

	if (Input::GetKey(KeyCode_Left))
	{
		endPos.x -= moveValue;
	}

	if (Input::GetKey(KeyCode_Right))
	{
		endPos.x += moveValue;
	}

	if (Input::GetKey(KeyCode_Up))
	{
		endPos.y += moveValue;
	}

	if (Input::GetKey(KeyCode_Down))
	{
		endPos.y -= moveValue;
	}

	if (Input::GetKey(KeyCode_R))
	{
		endPos.z -= moveValue;
	}

	if (Input::GetKey(KeyCode_F))
	{
		endPos.z += moveValue;
	}

	endPos = m_target;

	float baseAngle;
	sm::Vec3 arm1Direction;
	sm::Vec3 arm2Direction;

	ArmResolver(
		m_arm1->GetPosition(),
		endPos,
		m_arm1Length,
		m_arm2Length,
		baseAngle,
		arm1Direction,
		arm2Direction);

	m_arm1->SetRotation(sm::Quat::LookRotation(arm1Direction));
	m_arm2->SetRotation(sm::Quat::LookRotation(arm2Direction));
	
	
	//GraphicsLog::AddSegment(endPos, endPos + sm::Vec3(0, 0.2f, 0.0f));
	//GraphicsLog::AddSegment(m_arm1->GetPosition(), m_arm1->GetPosition() + arm1Direction, sm::Vec3(1, 0, 0));
	//GraphicsLog::AddSegment(m_arm2->GetPosition(), m_arm2->GetPosition() + arm2Direction, sm::Vec3(0, 1, 0));	
}

void MechArm::ArmResolver(
	const sm::Vec3 &basePosition,
	const sm::Vec3 &targetPosition,
	float arm1Length,
	float arm2Length,
	float& baseAngle,
	sm::Vec3& arm1Direction,
	sm::Vec3& arm2Direction)
{
	//float targetDistance = MathUtils::Clamp((targetPosition - basePosition).GetLength(), 0.0f, arm1Length + arm2Length);
	float targetDistance = MathUtils::Clamp((targetPosition - basePosition).GetLength(), 0.0f, (arm1Length + arm2Length) * 0.999f);

	float d2 = ((arm2Length * arm2Length) - (arm1Length * arm1Length) + (targetDistance * targetDistance)) / (2 * targetDistance);
	float h = sqrt((arm2Length * arm2Length) - (d2 * d2));

	sm::Vec3 targetDirection = (targetPosition - basePosition).GetNormalized();
	sm::Vec3 axis = (targetDirection * sm::Vec3(0, 1, 0)).GetNormalized();
	sm::Vec3 hDirection = axis * targetDirection;

	sm::Vec3 arm1Position = basePosition + (targetDirection * (targetDistance - d2)) + hDirection * h;

	arm1Direction = (arm1Position - basePosition).GetNormalized();
	arm2Direction = (targetPosition - arm1Position).GetNormalized();

	//baseTransform = CalcBoneMatrixZ(basePosition, sm::Vec3(targetPosition.x, basePosition.y, targetPosition.z));
	//arm1Transform = CalcBoneMatrixZ(basePosition, arm1Position);
	//arm2Transform = CalcBoneMatrixZ(arm1Position, targetPosition);
}
