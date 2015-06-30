#include "Behaviour.h"

Behaviour::Behaviour(GameObject* gameObject, const std::string& name) :
	Component(name, gameObject)
{
}
