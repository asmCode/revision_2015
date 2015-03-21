#pragma once

#include "../Behaviour.h"
#include <Math/Vec3.h>
#include <string>

class GameObject;

class Tile : public Behaviour
{
public:
	Tile(GameObject* gameObject, const std::string& name);

	void Update();

	void Blow();

private:
	sm::Vec3 m_velocity;
};
