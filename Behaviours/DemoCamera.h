#pragma once

#include "../Behaviour.h"
#include <Graphics/Point.h>
#include <string>

class GameObject;

class DemoCamera : public Behaviour
{
public:
	DemoCamera(GameObject* gameObject, const std::string& name);

	void Update();

private:
};
