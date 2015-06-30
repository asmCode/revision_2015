#pragma once

#include "GameObject.h"
#include <string>

class Component
{
public:
	Component(const std::string& componentName, GameObject* gameObject);
	virtual ~Component() {};

	GameObject* GetGameObject() const;

	const std::string& GetComponentName() const;

protected:
	GameObject* m_gameObject;
	std::string m_componentName;
};
