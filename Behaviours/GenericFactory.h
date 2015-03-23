#pragma once

#include "../IBehaviourFactory.h"

template <typename T>
class GenericFactory : public IBehaviourFactory
{
public:
	Behaviour* Create(GameObject* gameObject, const std::string& name)
	{
		return new T(gameObject, name);
	}
};
