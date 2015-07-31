#pragma once

#include "IAnimationCurve.h"
#include "../MathUtils.h"
#include "../Quat.h"

template <typename T>
class QuarticIn : public IAnimationCurve<T>
{
public:
	T Evaluate(const T& begin, const T& end, float time)
	{
		time = MathUtils::Clamp(time, 0.0f, 1.0f);

		T c = end - begin;

		return c*time*time*time*time + begin;
	};

};

template <>
sm::Quat QuarticIn<sm::Quat>::Evaluate(const sm::Quat& begin, const sm::Quat& end, float time)
{
	QuarticIn<float> timeCurve;

	float quatTime = timeCurve.Evaluate(0.0f, 1.0f, time);

	return sm::Quat::Slerp(begin, end, quatTime);
}
