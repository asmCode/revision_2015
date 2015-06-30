#pragma once

#include "Component.h"

class Light : public Component
{
public:
	static const std::string LightComponentName;

	Light(GameObject* gameObject);
};
