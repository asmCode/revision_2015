#include "AnimationTest.h"
#include "../FuturisEngine/PropertyContainer.h"
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
}

void AnimationTest::Update()
{
	if (Input::GetKeyDown(KeyCode_Z))
	{
		/*
		Camera* m_camera = (Camera*)ScenesManager::GetInstance()->FindGameObject("kamerka")->GetComponent(Camera::CameraComponentName);
		m_camera->GetPropertyContainer()->GetProperty("fov")->Set<float>(0.2f);
		*/
	}
}

