#pragma once

#include "SequenceBase.h"
#include <string>
#include <vector>

class GameObject;
class Sphere;
class MainCamera;
class SmoothNoise;

class OutroSequence : public SequenceBase
{
public:
	OutroSequence(Sphere* sphere, MainCamera* mainCamera);

	void Initialize();
	void Prepare();
	void Clean();
	void Update();
	void NotifySynchEvent(SynchEvent* synchEvent);

private:
	Sphere* m_sphere;
	MainCamera* m_mainCamera;
	SmoothNoise* m_smoothNoise;

	void PullOutLong();
};
