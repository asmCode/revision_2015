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
class EndlessFlightSequence;
class OutroSequence;
class MainCamera;

class SceneController : public Behaviour,
						public SynchManagerObserver
{
public:
	SceneController(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

private:
	Sphere* m_commonSphere;
	MainCamera* m_mainCamera;
	GameObject* m_spherePrefab;
	GameObject* m_mechArmPrefab;

	SequenceBase* m_currentSequence;
	BeginningSequence* m_beginningSequence;
	ExplosionsSequence* m_explosionsSequence;
	MagnetSequence* m_magnetSequence;
	EndlessFlightSequence* m_endlessFlightSequence;
	OutroSequence* m_outroSequence;

	void SynchEventFired(SynchEvent* synchEvent);
	void ChangeSequence(SequenceBase* sequence);
};
