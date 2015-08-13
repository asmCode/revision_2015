#pragma once

#include "../Behaviour.h"
#include <string>
#include <vector>

class GameObject;
class SpherePart;
class MechArm;

class Sphere : public Behaviour
{
public:
	Sphere(GameObject* gameObject, const std::string& name);

	void Initialize(GameObject* mechArmPrefab);
	void Update();
	void Awake();

	void RollSpherePart(int index);
	void BlinkSpherePart(int index, const sm::Vec3& color);
	void OpenWithMechArms();
	void ShowMechArms(bool show);

private:
	std::vector<SpherePart*> m_parts;
	std::vector<MechArm*> m_mechArms;

	void CreateMechArms(GameObject* mechArmPrefab);
};
