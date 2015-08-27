#pragma once

#include "IAnimationCurve.h"
#include "../MathUtils.h"
#include "../Quat.h"
#include <math.h>

template <typename T>
class QuadInOut : public IAnimationCurve<T>
{
public:
	T Evaluate(const T& begin, const T& end, float time)
	{
		time = MathUtils::Clamp(time, 0.0f, 1.0f);

		T c = end - begin;

		//return c * time * time + begin;

		time *= 2.0f;

		if (time < 1)
			return c / 2.0f * time * time + begin;

		time -= 1.0f;

		return -c / 2.0f * (time * (time - 2) - 1) + begin;
	};
};

template <>
sm::Quat QuadInOut<sm::Quat>::Evaluate(const sm::Quat& begin, const sm::Quat& end, float time)
{
	QuadInOut<float> timeCurve;

	float quatTime = timeCurve.Evaluate(0.0f, 1.0f, time);

	return sm::Quat::Slerp(begin, end, quatTime);
}
