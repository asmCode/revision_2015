#pragma once

#include "../IBehaviourFactory.h"

class JumpFactory
{
public:
	Behaviour* Create(GameObject* gameObject, const std::string& name);
};
