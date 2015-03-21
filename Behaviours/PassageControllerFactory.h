#pragma once

#include "../IBehaviourFactory.h"

class PassageControllerFactory : public IBehaviourFactory
{
public:
	Behaviour* Create(GameObject* gameObject, const std::string& name);
};
