#include "Component.h"

Component::Component(GameObject* gameObject) :
	m_gameObject(gameObject)
{
}

GameObject* Component::GetGameObject() const
{
	return m_gameObject;
}
