#pragma once

#include "../Behaviour.h"
#include <string>

class GameObject;

class SpherePart : public Behaviour
{
public:
	SpherePart(GameObject* gameObject, const std::string& name);

	void Update();
	void Awake();

private:
};
