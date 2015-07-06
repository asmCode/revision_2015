#include "AnimationPropertyAttachement.h"
#include "PropertyAnimationData.h"
#include "../PropertyWrapper.h"
#include "../PropertyType.h"
#include <Math/Vec3.h>
#include <Math/Quat.h>

AnimationPropertyAttachement::AnimationPropertyAttachement(
	const PropertyAnimationData* propertyAnimationData,
	PropertyWrapperBase* propertyWrapper) :
	m_setTimePointer(NULL),
	m_propertyAnimationData(propertyAnimationData),
	m_propertyWrapper(propertyWrapper)
{
	switch (propertyAnimationData->GetType())
	{
	case PropertyType_Int:
		break;
	case PropertyType_Float:
		m_setTimePointer = &AnimationPropertyAttachement::SetTimeT < float >;
		break;
	case PropertyType_Vec2:
		break;
	case PropertyType_Vec3:
		m_setTimePointer = &AnimationPropertyAttachement::SetTimeT < sm::Vec3 >;
		break;
	case PropertyType_Vec4:
		break;
	case PropertyType_Quat:
		m_setTimePointer = &AnimationPropertyAttachement::SetTimeT < sm::Quat >;
		break;
	case PropertyType_Matrix:
		break;
	case PropertyType_Texture:
		break;
	default:
		break;
	}
}

void AnimationPropertyAttachement::SetTime(float time)
{
	(this->*m_setTimePointer)(time);
}

