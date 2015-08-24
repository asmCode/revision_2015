#pragma once

#include "../../CommandBase.h"
#include "../MainCamera.h"
#include <Math/Vec3.h>

namespace MainCameraCommands
{
	class HeadBang : public CommandBase<MainCamera*>
	{
	public:
		HeadBang(float duration, float distance);
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
