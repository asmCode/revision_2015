#pragma once

#include "../../CommandBase.h"
#include "../../PropertyWrapper.h"
#include "../../FuturisEngine/Time.h"
#include <Math/Animation/IAnimationCurve.h>
#include <Math/Vec3.h>
#include <Math/Quat.h>

namespace TweenCommands
{
	template <typename T>
	class TweenProperty : public CommandBase
	{
	public:
		TweenProperty(
			PropertyWrapper<T>* property,
			IAnimationCurve<T>* curve,
			float duration,
			T dstValue) :
			m_property(property),
			m_curve(curve),
			m_time(0.0f),
			m_duration(duration),
			m_dstValue(dstValue)
		{
		}

		virtual ~TweenProperty() {}

		void Enter()
		{
			m_srcValue = m_property->Get();
			m_dstValue = m_dstValue * m_srcValue;
		}

		bool Update()
		{
			m_time += Time::DeltaTime;

			T value = m_curve->Evaluate(m_srcValue, m_dstValue, m_time / m_duration);
			m_property->Set(value);

			return m_time >= m_duration;
		}

	protected:
		PropertyWrapper<T>* m_property;
		IAnimationCurve<T>* m_curve;

		float m_time;
		float m_duration;
		T m_srcValue;
		T m_dstValue;
	};
}
