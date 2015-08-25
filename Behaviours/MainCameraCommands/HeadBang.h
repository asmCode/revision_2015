#pragma once

#include "MainCameraCommandBase.h"
#include "../MainCamera.h"
#include <Math/Vec3.h>

namespace MainCameraCommands
{
	class HeadBang : public MainCameraCommandBase
	{
	public:
		HeadBang(MainCamera* mainCamera, float duration, float distance);
		~HeadBang();

		void Enter();
		bool Update();

	private:
		float m_duration;
		float m_distance;

		sm::Vec3 m_forward;
		sm::Vec3 m_dstPos;

		float m_time;
	};
}
