#pragma once

#include "MainCameraCommandBase.h"
#include "../MainCamera.h"
#include <Math/Vec3.h>
#include <Math/Quat.h>
#include <string>

class Animation;
class AnimationClip;

namespace MainCameraCommands
{
	class Animation : public MainCameraCommandBase
	{
	public:
		Animation(MainCamera* mainCamera, const std::string& clipName);

		void Enter();
		bool Update();

	private:
		::Animation* m_animation;
		AnimationClip* m_clip;
	};
}
