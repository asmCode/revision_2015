#pragma once

class AnimationClip;

class Animation
{
public:
	Animation();

	void Play();
	void Stop();
	void SetAnimationClip(AnimationClip* animationClip);
	void SetTime(float time);
	void SetNormalizedTime(float normalizedTime);

	void Update();

private:
	AnimationClip* m_animationClip;

	float m_time;
};
