#include "MainCamera.h"
#include "Noise.h"
#include "SmoothNoise.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../Camera.h"
#include "../FuturisEngine/Time.h"
#include "../FuturisEngine/Animation/Animation.h"
#include "../GraphicsLog.h"
#include "../CommandBase.h"
#include "MainCameraCommands/HeadBang.h"
#include "MainCameraCommands/Orbit.h"
#include "MainCameraCommands/Roll.h"
#include "MainCameraCommands/Animation.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include <Math/MathUtils.h>

MainCamera::MainCamera(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_lookTransform(nullptr),
	m_noiseTransform(nullptr),
	m_camera(nullptr),
	m_noise(nullptr),
	m_smoothNoise(nullptr)
{
}

void MainCamera::Awake()
{
	m_camera = dynamic_cast<Camera*>(GetGameObject()->GetComponent("Camera"));
	m_pivotTransform = GetGameObject()->GetTransform().GetParent();
	m_lookTransform = &GetGameObject()->FindChild("MainCamera.Look")->GetTransform();
	m_noiseTransform = &m_lookTransform->GetGameObject()->FindChild("MainCamera.Noise")->GetTransform();
	m_noise = dynamic_cast<Noise*>(m_noiseTransform->GetGameObject()->GetComponent("Noise"));
	m_smoothNoise = dynamic_cast<SmoothNoise*>(m_noiseTransform->GetGameObject()->GetComponent("SmoothNoise"));
	m_animation = dynamic_cast<Animation*>(GetGameObject()->GetComponent("Animation"));

	m_smoothNoise->RotationNoise(0.3f, 0.04f);
	m_smoothNoise->TranslationNoise(0.3f, 3.04f);
}

void MainCamera::Update()
{
	ProcessCommands();

	if (Input::GetKeyDown(KeyCode_A))
	{
		QueueCommand(new MainCameraCommands::Animation(this, "cam01-01"));
		QueueCommand(new MainCameraCommands::Animation(this, "cam01-02"));
		QueueCommand(new MainCameraCommands::Animation(this, "cam01-03"));
		QueueCommand(new MainCameraCommands::Animation(this, "cam01-04"));
	}
	if (Input::GetKeyDown(KeyCode_H))
	{
		HeadBang();
	}
	if (Input::GetKeyDown(KeyCode_O))
	{
		Orbit();
		SetCommandParaller(new MainCameraCommands::Roll(this, 0.3f, -0.2f, 0.2f));
	}
	if (Input::GetKeyDown(KeyCode_I))
	{
		OrbitFast();
	}
	if (Input::GetKeyDown(KeyCode_R))
	{
		SetCommandParaller(new MainCameraCommands::Roll(this, 0.3f, -MathUtils::PI2, MathUtils::PI2));
	}

	m_animation->Update();
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
	SetCommandParaller(new MainCameraCommands::HeadBang(this, 0.4f, 0.5f));
}

void MainCamera::Orbit()
{
	SetCommandParaller(new MainCameraCommands::Orbit(this, 0.3f, 0.2f, 0.5f));
}

void MainCamera::OrbitFast()
{
	SetCommandParaller(new MainCameraCommands::Orbit(this, 0.3f, MathUtils::PI - 0.1f, MathUtils::PI - 0.1f, sm::Vec3(0, 1, 0)));
}

void MainCamera::OrbitSequence()
{
	return;

	QueueCommand(new MainCameraCommands::Orbit(this, 0.32f, 0.2f, 0.5f));
	QueueCommand(new MainCameraCommands::Orbit(this, 0.32f, 0.2f, 0.5f));
	QueueCommand(new MainCameraCommands::Orbit(this, 0.32f, 0.2f, 0.5f));
	QueueCommand(new MainCameraCommands::Orbit(this, 0.3f, MathUtils::PI - 0.1f, MathUtils::PI - 0.1f, sm::Vec3(0, 1, 0)));
}

