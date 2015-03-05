#pragma once

#include "GameObject.h"

class Component
{
public:
	Component(GameObject* gameObject);
	virtual ~Component() {};

	GameObject* GetGameObject() const;

protected:
	GameObject* m_gameObject;
};
