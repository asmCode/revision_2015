#pragma once

#include "../Behaviour.h"
#include <Graphics/Point.h>
#include <string>

class GameObject;
class Animation;

class AnimationTest : public Behaviour
{
public:
	AnimationTest(GameObject* gameObject, const std::string& name);

	void Update();
	void Awake();

private:
	float m_time;

	Animation* m_animation;
};
