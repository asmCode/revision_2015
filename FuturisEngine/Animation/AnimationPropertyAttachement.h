#pragma once

#include <Math/Animation/AnimationCurve.h>

class PropertyAnimationData;
class PropertyWrapperBase;

class AnimationPropertyAttachement
{
public:
	AnimationPropertyAttachement(
		const PropertyAnimationData* propertyAnimationData,
		PropertyWrapperBase* propertyWrapper);

	void SetTime(float time);

private:
	using SetTimePointer = void (AnimationPropertyAttachement::*)(float);

	SetTimePointer m_setTimePointer;

	const PropertyAnimationData* m_propertyAnimationData;
	PropertyWrapperBase* m_propertyWrapper;

	template <typename T>
	void SetTimeT(float time)
	{
		T value = ((AnimationCurve<T>*)m_propertyAnimationData->GetAnimationCurve())->Evaluate(time);
		((PropertyWrapper<T>*)m_propertyWrapper)->Set(value);
	}
};

