#include "AnimationClip.h"
#include "PropertyAnimationData.h"
#include <Math/MathUtils.h>
#include <assert.h>
#include <stdint.h>

AnimationClip::AnimationClip(const std::string& name) :
	m_name(name),
	m_duration(0.0f)
{
}

AnimationClip::~AnimationClip()
{
	// TODO: ktos musi PropertyAnimationData 
}

void AnimationClip::AddPropertyAnimation(PropertyAnimationData* propertyAnimationData)
{
	m_propertyAnimations.push_back(propertyAnimationData);

	m_duration = MathUtils::Max(m_duration, propertyAnimationData->GetDuration());
}

int AnimationClip::GetPropertyAnimationsCount() const
{
	return (int)m_propertyAnimations.size();
}

float AnimationClip::GetDuration() const
{
	return m_duration;
}

const PropertyAnimationData* AnimationClip::GetPropertyAnimation(int index) const
{
	assert(m_propertyAnimations.size() > (uint32_t)index);

	return m_propertyAnimations[index];
}

