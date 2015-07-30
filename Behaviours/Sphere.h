#pragma once

#include "../Behaviour.h"
#include <string>
#include <vector>

class GameObject;
class SpherePart;

class Sphere : public Behaviour
{
public:
	Sphere(GameObject* gameObject, const std::string& name);

	void Update();
	void Awake();

	void RollSpherePart(int index);
	void BlinkSpherePart(int index, const sm::Vec3& color);

private:
	std::vector<SpherePart*> m_parts;
};
