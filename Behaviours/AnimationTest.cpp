#include "AnimationTest.h"
#include "../FuturisEngine/PropertyContainer.h"
#include "../FuturisEngine/Animation/Animation.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Camera.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"

AnimationTest::AnimationTest(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void AnimationTest::Awake()
{
	m_animation = (Animation*)ScenesManager::GetInstance()->FindGameObject("root")->GetComponent("Animation");
	m_animation->Play();
}

float time = 0.0f;

void AnimationTest::Update()
{
	bool changedTime = false;

	if (Input::GetKey(KeyCode_O))
	{
		time += Time::DeltaTime;
		changedTime = true;
	}

	if (Input::GetKey(KeyCode_K))
	{
		time -= Time::DeltaTime;
		changedTime = true;
	}

	if (changedTime)
		m_animation->SetTime(time);
}

