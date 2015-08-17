#pragma once

#include "SequenceBase.h"
#include <string>
#include <vector>

class GameObject;
class Sphere;
class Camera;

class BeginningSequence : public SequenceBase
{
public:
	BeginningSequence(GameObject* spherePrefab, GameObject* mechArmPrefab, Camera* mainCamera);

	void Initialize();
	void Prepare();
	void Clean();
	void Update();
	void NotifySynchEvent(SynchEvent* synchEvent);

private:
	GameObject* m_spherePrefab;
	GameObject* m_mechArmPrefab;
	Sphere* m_sphere;
	Camera* m_mainCamera;

	GameObject* m_cameraPivot;
	float m_cameraAngle;

	int m_pullOutLongBaseIndex;

	void PullOutLong();
};
