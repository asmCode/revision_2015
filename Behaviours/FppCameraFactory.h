#pragma once

#include "../IBehaviourFactory.h"

class FppCameraFactory : public IBehaviourFactory
{
public:
	Behaviour* Create(GameObject* gameObject, const std::string& name);
};
