#pragma once

#include "SequenceBase.h"
#include <string>
#include <vector>

class GameObject;
class Sphere;
class Camera;

class ExplosionsSequence : public SequenceBase
{
public:
	ExplosionsSequence(GameObject* spherePrefab, GameObject* m_mechArmPrefab, Camera* mainCamera);

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
	Camera* m_mainCamera;

	float m_speed;

	void SwapSpheres();
	void ResetSphere(Sphere* sphere);
	void ExplodeSphere(Sphere* sphere);
};
