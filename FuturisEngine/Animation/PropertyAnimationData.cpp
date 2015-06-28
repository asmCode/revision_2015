#include "PropertyAnimationData.h"
#include <Math/Animation/AnimationCurve.h>
#include <Math/Vec3.h>
#include <Math/Quat.h>

PropertyAnimationData::PropertyAnimationData(
	Parameter::Type type,
	std::string targetName,
	std::string componentType,
	std::string propertyName,
	void* animationCurve) :
	m_type(type),
	m_targetName(targetName),
	m_componentType(componentType),
	m_propertyName(propertyName),
	m_animationCurve(animationCurve)
{
}

Parameter::Type PropertyAnimationData::GetType() const
{
	return m_type;
}

const std::string& PropertyAnimationData::GetTargetName() const
{
	return m_targetName;
}

const std::string& PropertyAnimationData::GetComponentType() const
{
	return m_componentType;
}

const std::string& PropertyAnimationData::GetPropertyName() const
{
	return m_propertyName;
}

void* PropertyAnimationData::GetAnimationCurve() const
{
	return m_animationCurve;
}

float PropertyAnimationData::GetDuration() const
{
	switch (m_type)
	{
	case Parameter::Type_Float:
		return ((AnimationCurve<float>*)m_animationCurve)->GetEndTime();
	case Parameter::Type_Int:
		return ((AnimationCurve<int>*)m_animationCurve)->GetEndTime();
	case Parameter::Type_Vec3:
		return ((AnimationCurve<sm::Vec3>*)m_animationCurve)->GetEndTime();
	case Parameter::Type_Quat:
		return ((AnimationCurve<sm::Quat>*)m_animationCurve)->GetEndTime();
	}

	return 0.0f;
}

