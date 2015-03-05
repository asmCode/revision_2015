#pragma once

#include "Component.h"
#include <string>

class Behaviour : public Component
{
public:
	Behaviour(GameObject* gameObject, const std::string& name);
	virtual ~Behaviour() {};

	const std::string& GetName() const;

	virtual void Awake() {};
	virtual void Update() {};

protected:
	std::string m_name;
};
