#pragma once

#include "../Behaviour.h"
#include <Graphics/Point.h>
#include <string>

class GameObject;

class AnimationTest : public Behaviour
{
public:
	AnimationTest(GameObject* gameObject, const std::string& name);

	void Update();
	void Awake();

private:
	GameObject* m_objects[3];
	int m_activeObject;
};
