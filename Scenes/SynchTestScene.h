#pragma once

#include "BaseScene.h"
#include <vector>

class BlinkStatic;

class SynchTestScene : public BaseScene
{
public:
	bool Update(float time, float deltaTime);

private:
	std::vector<BlinkStatic*> m_blinks;

	void InitializeSubScene();

	void NotifySynchEvent(SynchEvent* synchEvent);
};
