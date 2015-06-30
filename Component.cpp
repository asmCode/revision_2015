#include "Component.h"

Component::Component(const std::string& componentName, GameObject* gameObject) :
	m_componentName(componentName),
	m_gameObject(gameObject)
{
}

GameObject* Component::GetGameObject() const
{
	return m_gameObject;
}

const std::string& Component::GetComponentName() const
{
	return m_componentName;
}

