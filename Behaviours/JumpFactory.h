#pragma once

#include "../IBehaviourFactory.h"

class JumpFactory : public IBehaviourFactory
{
public:
	Behaviour* Create(GameObject* gameObject, const std::string& name);
};
