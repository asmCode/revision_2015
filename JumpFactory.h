#pragma once

#include <string>

class Behaviour;
class GameObject;

class IBehaviourFactory
{
public:
	virtual ~IBehaviourFactory() {};
	
	virtual Behaviour* Create(GameObject* gameObject, const std::string& name) = 0;
};
