#include "Animation.h"
#include "../../Transform.h"
#include "../../GameObject.h"
#include "../../FuturisEngine/Animation/Animation.h"
#include "../../FuturisEngine/Animation/AnimationClip.h"
#include "../../FuturisEngine/Time.h"
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Math/Animation/QuarticOut.h>
#include <Math/Animation/LinearCurve.h>
#include <Math/Animation/Custom/BlinkCurve.h>
#include <Graphics/Content/Content.h>
#include <Utils/Random.h>

namespace MainCameraCommands
{
	Animation::Animation(MainCamera* mainCamera, const std::string& clipName) :
		MainCameraCommandBase(mainCamera)
	{
		m_clip = Content::Instance->Get<AnimationClip>(clipName);
	}

	void Animation::Enter()
	{
		m_animation = dynamic_cast<::Animation*>(m_subject->GetGameObject()->GetComponent("Animation"));
		m_animation->SetAnimationClip(m_clip);
		m_animation->Play();
	}

	bool Animation::Update()
	{
		return m_animation->Finished();
	}
}
