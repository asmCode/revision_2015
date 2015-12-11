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
	m_isPlaying(false),
	m_attachement(NULL)
{
}

void Animation::Play()
{
	if (m_animationClip == NULL || m_isPlaying)
		return;

	m_isPlaying = true;
}

void Animation::Stop()
{
	m_isPlaying = false;

	if (m_animationClip == NULL)
		return;
}

void Animation::SetAnimationClip(AnimationClip* animationClip)
{
	m_time = 0.0f;

	if (m_attachement != NULL)
		delete m_attachement;

	m_animationClip = animationClip;

	m_attachement = new AnimationClipAttachement(m_animationClip, GetGameObject());
}

void Animation::SetTime(float time)
{
	m_time = time;

	m_attachement->SetTime(fmodf(time, m_animationClip->GetDuration()));
}

void Animation::SetNormalizedTime(float normalizedTime)
{
	if (m_animationClip == NULL)
		return;
}

bool Animation::Finished() const
{
	if (m_animationClip == nullptr)
		return false;

	return m_time >= m_animationClip->GetDuration();
}

void Animation::Update()
{
	if (!m_isPlaying)
		return;

	m_time += Time::DeltaTime;

	SetTime(m_time);
}
