#pragma once

#include "../Behaviour.h"
#include <string>

class GameObject;

class FppCamera : public Behaviour
{
public:
	FppCamera(GameObject* gameObject, const std::string& name);

	void Update();

private:
	float m_speed;
	float m_power;
};
