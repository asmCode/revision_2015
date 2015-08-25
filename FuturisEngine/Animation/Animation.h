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

	bool Finished() const; // tymczasowa metoda do sprawdzania czy czas przekroczyl czas clipu. Zrefaktoruj to jakos

private:
	AnimationClip* m_animationClip;

	float m_time;
	bool m_isPlaying;

	AnimationClipAttachement* m_attachement;
};
