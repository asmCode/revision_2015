#pragma once

#include "IAnimationCurve.h"
#include "../MathUtils.h"
#include <math.h>

template <typename T>
class QuadIn : public IAnimationCurve<T>
{
public:
	T Evaluate(const T& begin, const T& end, float time)
	{
		time = MathUtils::Clamp(time, 0.0f, 1.0f);

		T c = end - begin;

		return c * time * time + begin;
	};
};

template <>
sm::Quat QuadIn<sm::Quat>::Evaluate(const sm::Quat& begin, const sm::Quat& end, float time)
{
	QuadIn<float> timeCurve;

	float quatTime = timeCurve.Evaluate(0.0f, 1.0f, time);

	return sm::Quat::Slerp(begin, end, quatTime);
}
