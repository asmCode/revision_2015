#pragma once

#include "../IBehaviourFactory.h"

class TileFactory : public IBehaviourFactory
{
public:
	Behaviour* Create(GameObject* gameObject, const std::string& name);
};
