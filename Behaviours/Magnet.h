#pragma once

#include "../Behaviour.h"
#include <Math/Quat.h>
#include <Math/Vec3.h>
#include <string>

class GameObject;
class Transform;

class Magnet : public Behaviour
{
public:
	Magnet(GameObject* gameObject, const std::string& name);

	void Initialize(Transform* parent);
	void Awake();
	void Update();

private:
	float m_xAngle;
	float m_xAngleSpeed;
	float m_yAngle;
	float m_yAngleSpeed;
	float m_zAngle;
	float m_zAngleSpeed;

	GameObject* m_pivot;
};
