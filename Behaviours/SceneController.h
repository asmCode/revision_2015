#pragma once

#include "../Behaviour.h"
#include "../SynchManagerObserver.h"
#include <string>

class GameObject;
class Sphere;
class SynchEvent;
class Camera;
class SequenceBase;
class BeginningSequence;
class ExplosionsSequence;
class MagnetSequence;

class SceneController : public Behaviour,
						public SynchManagerObserver
{
public:
	SceneController(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

private:
	Sphere* m_commonSphere;
	Camera* m_mainCamera;
	GameObject* m_spherePrefab;
	GameObject* m_mechArmPrefab;

	SequenceBase* m_currentSequence;
	BeginningSequence* m_beginningSequence;
	ExplosionsSequence* m_explosionsSequence;
	MagnetSequence* m_magnetSequence;

	void SynchEventFired(SynchEvent* synchEvent);
	void ChangeSequence(SequenceBase* sequence);
};
