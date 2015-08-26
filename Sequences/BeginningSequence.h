#pragma once

#include "SequenceBase.h"
#include <string>
#include <vector>
#include "../../CommandHandler.h"

class GameObject;
class Sphere;
class MainCamera;
class PlaneObject;

class BeginningSequence : public SequenceBase, public CommandHandler<BeginningSequence>
{
public:
	BeginningSequence(Sphere* sphere, MainCamera* mainCamera);

	void Initialize();
	void Prepare();
	void Clean();
	void Update();
	void NotifySynchEvent(SynchEvent* synchEvent);

private:
	Sphere* m_sphere;
	MainCamera* m_mainCamera;
	PlaneObject* m_groupPlane;
	PlaneObject* m_titlePlane;

	GameObject* m_cameraPivot;
	float m_cameraAngle;

	int m_pullOutLongBaseIndex;

	void PullOutLong();
};
