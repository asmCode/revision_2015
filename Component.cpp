#include "Component.h"
#include "FuturisEngine/PropertyContainer.h"

Component::Component(const std::string& componentName, GameObject* gameObject) :
	m_componentName(componentName),
	m_gameObject(gameObject),
	m_isDestroyed(false)
{
	m_propertyContainer = new PropertyContainer();
}

GameObject* Component::GetGameObject() const
{
	return m_gameObject;
}

PropertyContainer* Component::GetPropertyContainer() const
{
	return m_propertyContainer;
}

void Component::SetDestroyed()
{
	m_isDestroyed = true;
}

bool Component::IsDestroyed() const
{
	return m_isDestroyed;
}

const std::string& Component::GetComponentName() const
{
	return m_componentName;
}

