#pragma once

#include "Component.h"
#include "../FuturisEngine/ParametersContainer.h"
#include <string>

class Behaviour : public Component, public ParametersContainer
{
public:
	Behaviour(GameObject* gameObject, const std::string& name);
	virtual ~Behaviour() {};

	virtual void Awake() {};
	virtual void Update() {};
};
