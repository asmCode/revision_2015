#pragma once

#include "../Behaviour.h"
#include <Graphics/Point.h>
#include <Math/Quat.h>
#include <string>

class GameObject;

class CameraPivot : public Behaviour
{
public:
	CameraPivot(GameObject* gameObject, const std::string& name);

	void Update();

private:
	float m_speed;

	float m_angle;

	sm::Quat m_baseRotation;
};
