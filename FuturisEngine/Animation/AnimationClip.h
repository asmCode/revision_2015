#pragma once

#include <string>
#include <vector>

class PropertyAnimationData;

class AnimationClip
{
public:
	AnimationClip(const std::string& name);
	~AnimationClip();

	void AddPropertyAnimation(PropertyAnimationData* propertyAnimationData);

	int GetPropertyAnimationsCount() const;
	const PropertyAnimationData* GetPropertyAnimation(int index) const;

private:
	std::string	m_name;
	float m_duration;
	std::vector<PropertyAnimationData*> m_propertyAnimations;
};
