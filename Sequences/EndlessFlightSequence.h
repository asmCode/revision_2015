#pragma once

#include "SequenceBase.h"
#include <Math/Animation/AnimationCurve.h>
#include <Math/Vec3.h>
#include <string>
#include <vector>

class GameObject;
class Sphere;
class SpherePart;
class Camera;

class EndlessFlightSequence : public SequenceBase
{
public:
	EndlessFlightSequence(GameObject* spherePrefab, GameObject* m_mechArmPrefab, Camera* mainCamera);

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
	AnimationCurve<sm::Vec3>* m_cameraCurve;

	float m_speed;

	void SwapSpheres();
	void ResetSphere(Sphere* sphere);
	void ExplodeSphere(Sphere* sphere);

	SpherePart* GetRandomPart(Sphere* sphere);
	AnimationCurve<sm::Vec3>* CreateCurve(const sm::Vec3& start, const sm::Vec3& end, const sm::Vec3& pivot);
};
