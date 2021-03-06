#pragma once

#include "SequenceBase.h"
#include <string>
#include <vector>

class GameObject;
class Sphere;
class MainCamera;
class PlaneObject;

class ExplosionsSequence : public SequenceBase
{
public:
	ExplosionsSequence(GameObject* spherePrefab, GameObject* m_mechArmPrefab, MainCamera* mainCamera);

	void Initialize();
	void Prepare();
	void Update();
	void Clean();
	void NotifySynchEvent(SynchEvent* synchEvent);

	void Repeat();

private:
	GameObject* m_spherePrefab;
	GameObject* m_mechArmPrefab;
	Sphere* m_normalSphere;
	Sphere* m_smallSphere;
	MainCamera* m_mainCamera;

	float m_speed;

	void SwapSpheres();
	void ResetSphere(Sphere* sphere);
	void ExplodeSphere(Sphere* sphere);

	int m_greetzIndex;
	std::vector<PlaneObject*> m_greetz;
};
