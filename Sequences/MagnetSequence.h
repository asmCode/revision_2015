#pragma once

#include "SequenceBase.h"
#include <string>
#include <vector>

class GameObject;
class Sphere;
class MainCamera;
class Magnet;

class MagnetSequence : public SequenceBase
{
public:
	MagnetSequence(Sphere* sphere, MainCamera* mainCamera);

	void Initialize();
	void Prepare();
	void Clean();
	void Update();
	void NotifySynchEvent(SynchEvent* synchEvent);

private:
	Sphere* m_sphere;
	MainCamera* m_mainCamera;

	std::vector<Magnet*> m_magnets;

	void AddMagnet();
};
