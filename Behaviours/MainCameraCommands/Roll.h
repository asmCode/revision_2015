#pragma once

#include "MainCameraCommandBase.h"
#include "../MainCamera.h"
#include <Math/Vec3.h>
#include <Math/Quat.h>

namespace MainCameraCommands
{
	class Roll : public MainCameraCommandBase
	{
	public:
		Roll(MainCamera* mainCamera, float duration, float minAngle, float maxAngle);
		~Roll();

		void Enter();
		bool Update();

	private:
		float m_duration;
		float m_minAngle;
		float m_maxAngle;

		sm::Vec3 m_axis;
		sm::Quat m_srcRot;
		sm::Quat m_dstRot;

		float m_time;
	};
}
