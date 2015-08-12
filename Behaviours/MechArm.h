#pragma once

#include "../Behaviour.h"
#include <Math/Vec3.h>
#include <Math/Quat.h>
#include <string>

class GameObject;
class Transform;

class MechArm : public Behaviour
{
public:
	MechArm(GameObject* gameObject, const std::string& name);

	void Update();
	void Awake();

	void SetTarget(const sm::Vec3& target);

private:
	Transform* m_base;
	Transform* m_arm1;
	Transform* m_arm2;
	Transform* m_arrow;
	Transform* m_end;

	float m_arm1Length;
	float m_arm2Length;

	sm::Vec3 m_target;

	void MechArm::ArmResolver(
		const sm::Vec3 &basePosition,
		const sm::Vec3 &targetPosition,
		float arm1Length,
		float arm2Length,
		float& baseAngle,
		sm::Vec3& arm1Direction,
		sm::Vec3& arm2Direction);
};
