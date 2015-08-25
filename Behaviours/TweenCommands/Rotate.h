#pragma once

#include "../../CommandBase.h"
#include "../../Transform.h"
#include <Math/Animation/IAnimationCurve.h>
#include <Math/Vec3.h>
#include <Math/Quat.h>

namespace TweenCommands
{
	class Rotate : public CommandBase
	{
	public:
		Rotate(Transform* transform, IAnimationCurve<float>* curve, float duration, float angle, const sm::Vec3& axis);
		virtual ~Rotate();

		void Enter();
		bool Update();

	private:
		Transform* m_transform;
		IAnimationCurve<float>* m_curve;
		float m_duration;
		float m_angle;
		sm::Vec3 m_axis;
		sm::Quat m_baseRotation;

		float m_time;
	};
}
