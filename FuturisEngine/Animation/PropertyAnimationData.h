#pragma once

#include <string>
#include "../Parameter.h"

template<typename T> class AnimationCurve;

class PropertyAnimationData
{
public:
	PropertyAnimationData(
		Parameter::Type type,
		std::string targetName,
		std::string componentType,
		std::string propertyName,
		void* animationCurve);

	Parameter::Type GetType() const;
	const std::string& GetTargetName() const;
	const std::string& GetComponentType() const;
	const std::string& GetPropertyName() const;
	void* GetAnimationCurve() const;

	float GetDuration() const;

private:
	Parameter::Type m_type;
	std::string m_targetName;
	std::string m_componentType;
	std::string m_propertyName;

	void* m_animationCurve;
};
