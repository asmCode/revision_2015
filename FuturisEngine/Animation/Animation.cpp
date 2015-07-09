#include "Animation.h"
#include "AnimationClip.h"
#include "AnimationClipAttachement.h"
#include "../Time.h"
#include "../GameObject.h"
#include <assert.h>

Animation::Animation(GameObject* gameObject) :
	Component("Animation", gameObject),
	m_animationClip(NULL),
	m_time(0.0f),
	m_attachement(NULL)
{
}

void Animation::Play()
{
	if (m_animationClip == NULL)
		return;

	m_attachement = new AnimationClipAttachement(m_animationClip, GetGameObject());
}

void Animation::Stop()
{
	if (m_animationClip == NULL)
		return;
}

void Animation::SetAnimationClip(AnimationClip* animationClip)
{
	if (m_attachement != NULL)
		delete m_attachement;

	m_animationClip = animationClip;
}

void Animation::SetTime(float time)
{
	m_time = time;

	m_attachement->SetTime(time);
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
