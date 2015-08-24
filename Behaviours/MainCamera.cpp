#include "MainCamera.h"
#include "Noise.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../Camera.h"
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"
#include "../CommandBase.h"
#include "MainCameraCommands/HeadBang.h"
#include "MainCameraCommands/Orbit.h"
#include "MainCameraCommands/Roll.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include <Math/MathUtils.h>

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
	m_pivotTransform = GetGameObject()->GetTransform().GetParent();
	m_lookTransform = &GetGameObject()->FindChild("MainCamera.Look")->GetTransform();
	m_noiseTransform = &m_lookTransform->GetGameObject()->FindChild("MainCamera.Noise")->GetTransform();
	m_noise = dynamic_cast<Noise*>(m_noiseTransform->GetGameObject()->GetComponent("Noise"));

	//m_noise->RotationNoise(1.0f, 0.005f);
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
		SetCommandParaller(new MainCameraCommands::Roll(0.3f, -0.2f, 0.2f));
	}
	if (Input::GetKeyDown(KeyCode_I))
	{
		SetCommandParaller(new MainCameraCommands::Orbit(0.3f, MathUtils::PI2, MathUtils::PI2, sm::Vec3(0, 1, 0)));
	}
	if (Input::GetKeyDown(KeyCode_R))
	{
		SetCommandParaller(new MainCameraCommands::Roll(0.3f, -MathUtils::PI2, MathUtils::PI2));
	}
}

Transform* MainCamera::GetPivotTransform()
{
	return m_pivotTransform;
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

Noise* MainCamera::GetNoise()
{
	return m_noise;
}

void MainCamera::HeadBang()
{
	SetCommandParaller(new MainCameraCommands::HeadBang(0.4f, 3));
}

void MainCamera::Orbit()
{
	SetCommandParaller(new MainCameraCommands::Orbit(0.3f, 0.2f, 0.5f));
}
