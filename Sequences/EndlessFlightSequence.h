#pragma once

#include "SequenceBase.h"
#include <Math/Animation/AnimationCurve.h>
#include <Math/Vec3.h>
#include <string>
#include <vector>

class GameObject;
class Sphere;
class SpherePart;
class MainCamera;

class EndlessFlightSequence : public SequenceBase
{
public:
	EndlessFlightSequence(GameObject* spherePrefab, GameObject* m_mechArmPrefab, MainCamera* mainCamera);

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
	Sphere* m_tinySphere;
	MainCamera* m_mainCamera;
	AnimationCurve<sm::Vec3>* m_cameraCurve;

	float m_speed;
	float m_cameraTime;
	sm::Vec3 m_end;

	void SwapSpheres();
	void ResetSphere(Sphere* sphere);
	void ExplodeSphere(Sphere* sphere);

	SpherePart* GetRandomPart(Sphere* sphere);
	AnimationCurve<sm::Vec3>* CreateCurve(const sm::Vec3& start, Sphere* destinationSphere, const sm::Vec3& pivot);
	void Beat1();
	void BlinkSphere(Sphere* sphere);
};
