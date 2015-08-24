#include "MainCamera.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../Camera.h"
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"
#include "../CommandBase.h"
#include "MainCameraCommands/HeadBang.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>

MainCamera::MainCamera(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_lookTransform(nullptr),
	m_noiseTransform(nullptr),
	m_camera(nullptr)
{
}

void MainCamera::Awake()
{
	m_camera = dynamic_cast<Camera*>(GetGameObject()->GetComponent("Camera"));
	m_lookTransform = &GetGameObject()->FindChild("MainCamera.Look")->GetTransform();
	m_noiseTransform = &m_lookTransform->GetGameObject()->FindChild("MainCamera.Noise")->GetTransform();
}

void MainCamera::Update()
{
	ProcessCommands();

	if (Input::GetKeyDown(KeyCode_H))
	{
		HeadBang();
	}
	if (Input::GetKeyDown(KeyCode_O))
	{
		Orbit();
	}
}

Transform* MainCamera::GetRootTransform()
{
	return &GetGameObject()->GetTransform();
}

Transform* MainCamera::GetLookTransform()
{
	return m_lookTransform;
}

Transform* MainCamera::GetNoiseTransform()
{
	return m_noiseTransform;
}

Camera* MainCamera::GetCamera()
{
	return m_camera;
}

void MainCamera::HeadBang()
{
	SetCommandParaller(new MainCameraCommands::HeadBang(0.4f, 2));
}

void MainCamera::Orbit()
{

}
