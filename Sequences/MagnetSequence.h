#pragma once

#include "SequenceBase.h"
#include <string>
#include <vector>

class GameObject;
class Sphere;
class Camera;

class MagnetSequence : public SequenceBase
{
public:
	MagnetSequence(Sphere* sphere, Camera* mainCamera);

	void Initialize();
	void Prepare();
	void Clean();
	void Update();
	void NotifySynchEvent(SynchEvent* synchEvent);

private:
	Sphere* m_sphere;
	Camera* m_mainCamera;

	std::vector<GameObject*> m_magnet;

	void AddMagnet();
};
