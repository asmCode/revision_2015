#include "Behaviour.h"

Behaviour::Behaviour(GameObject* gameObject, const std::string& name) :
	Component(gameObject),
	m_name(name)
{
}

const std::string& Behaviour::GetName() const
{
	return m_name;
}
