#pragma once

#include <string>

class GameObject;
class PropertyContainer;

class Component
{
public:
	Component(const std::string& componentName, GameObject* gameObject);
	virtual ~Component() {};

	GameObject* GetGameObject() const;
	PropertyContainer* GetPropertyContainer() const;
	void SetDestroyed();
	bool IsDestroyed() const;

	const std::string& GetComponentName() const;

protected:
	GameObject* m_gameObject;
	std::string m_componentName;

private:
	PropertyContainer* m_propertyContainer;
	bool m_isDestroyed;
};
