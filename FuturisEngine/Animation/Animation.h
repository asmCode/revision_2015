#pragma once

#include "../../Component.h"

class AnimationClip;
class GameObject;
class AnimationClipAttachement;

class Animation : public Component
{
public:
	Animation(GameObject* gameObject);

	void Play();
	void Stop();
	void SetAnimationClip(AnimationClip* animationClip);
	void SetTime(float time);
	void SetNormalizedTime(float normalizedTime);

	void Update();

private:
	AnimationClip* m_animationClip;

	float m_time;

	AnimationClipAttachement* m_attachement;
};
