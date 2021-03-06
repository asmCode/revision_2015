#pragma once

#include "../Behaviour.h"
#include <string>

class GameObject;

class Jump : public Behaviour
{
public:
	Jump(GameObject* gameObject, const std::string& name);

	void Update();

private:
	float m_speed;
	float m_power;
};
