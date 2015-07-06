#include "AnimationClipAttachement.h"

#include "AnimationClip.h"
#include "PropertyAnimationData.h"
#include "AnimationPropertyAttachement.h"
#include "../Component.h"
#include "../../GameObject.h"
#include "../PropertyContainer.h"
#include <string>

AnimationClipAttachement::AnimationClipAttachement(
	AnimationClip* animationClip,
	GameObject* gameObject) :
	m_animationClip(animationClip),
	m_gameObject(gameObject)
{
	assert(m_animationClip != NULL);
	assert(m_gameObject != NULL);

	for (int i = 0; i < animationClip->GetPropertyAnimationsCount(); i++)
	{
		const PropertyAnimationData* animData = animationClip->GetPropertyAnimation(i);
		assert(animData != NULL);

		Component* component = m_gameObject->GetComponent(animData->GetComponentType());
		assert(component != NULL);

		PropertyContainer::Property* property = component->GetPropertyContainer()->GetProperty(animData->GetPropertyName());
		assert(property != NULL);

		assert(animData->GetType() == property->GetType());

		PropertyWrapperBase* propertyWrapper = property->GetPropertyWrapper();
		assert(propertyWrapper != NULL);

		AnimationPropertyAttachement* propertyAttachement = new AnimationPropertyAttachement(
			animData, propertyWrapper);

		m_attachements.push_back(propertyAttachement);
	}
}

AnimationClipAttachement::~AnimationClipAttachement()
{
	for (uint32_t i = 0; i < m_attachements.size(); i++)
		delete m_attachements[i];
}

void AnimationClipAttachement::SetTime(float time)
{
	for (uint32_t i = 0; i < m_attachements.size(); i++)
		m_attachements[i]->SetTime(time);
}
