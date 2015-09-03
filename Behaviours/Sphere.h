#pragma once

#include "../Behaviour.h"
#include "../CommandHandler.h"
#include <string>
#include <vector>

class GameObject;
class SpherePart;
class MechArm;
class Noise;
class SphereCommandBase;

class Sphere : public Behaviour, public CommandHandler<Sphere>
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

	void SpinFast();

	const std::vector<SpherePart*>& GetSphereParts() const;
	SpherePart* GetClosestPart(const sm::Vec3& position, int& index) const;

	Noise* GetNoise() const;

	void Reset();

private:
	std::vector<SpherePart*> m_parts;
	std::vector<MechArm*> m_mechArms;
	Noise* m_noise;

	void CreateMechArms(GameObject* mechArmPrefab);

	void SortSphereParts();
};
