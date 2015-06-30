#include "Animation.h"
#include "AnimationClip.h"
#include "../Time.h"
#include "../GameObject.h"
#include <assert.h>

Animation::Animation(GameObject* gameObject) :
	Component("Animation", gameObject),
	m_animationClip(NULL),
	m_time(0.0f)
{
}

void Animation::Play()
{
	if (m_animationClip == NULL)
		return;
}

void Animation::Stop()
{
	if (m_animationClip == NULL)
		return;
}

void Animation::SetAnimationClip(AnimationClip* animationClip)
{
	m_animationClip = animationClip;

	SetTime(0.0f);
}

void Animation::SetTime(float time)
{
	m_time = time;
}

void Animation::SetNormalizedTime(float normalizedTime)
{
	if (m_animationClip == NULL)
		return;
}

void Animation::Update()
{
	m_time += Time::DeltaTime;
}
