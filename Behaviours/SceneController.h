#pragma once

#include "../Behaviour.h"
#include "../SynchManagerObserver.h"
#include <string>

class GameObject;
class Sphere;
class SynchEvent;
class Camera;

class SceneController : public Behaviour,
						public SynchManagerObserver
{
public:
	SceneController(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

private:
	Camera* m_mainCamera;
	Sphere* m_spherePrefab;
	Sphere* m_sphere;

	void SynchEventFired(SynchEvent* synchEvent);
	void PrepareForExplosions();
};
