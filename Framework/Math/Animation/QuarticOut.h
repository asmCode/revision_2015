#pragma once

#include "IAnimationCurve.h"
#include "../MathUtils.h"
#include "../Quat.h"

template <typename T>
class QuarticOut : public IAnimationCurve<T>
{
public:
	T Evaluate(const T& begin, const T& end, float time)
	{
		time = MathUtils::Clamp(time, 0.0f, 1.0f);

		T c = end - begin;
		time--;
		return ((-c) * (time*time*time*time - 1)) + begin;
	};

};

template <>
sm::Quat QuarticOut<sm::Quat>::Evaluate(const sm::Quat& begin, const sm::Quat& end, float time)
{
	QuarticOut<float> timeCurve;

	float quatTime = timeCurve.Evaluate(0.0f, 1.0f, time);

	return sm::Quat::Slerp(begin, end, quatTime);
}
