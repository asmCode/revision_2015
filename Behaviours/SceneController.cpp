#include "SceneController.h"
#include "Sphere.h"
#include "BackCamera.h"
#include "MainCamera.h"
#include "../Camera.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../SynchManager.h"
#include "../SynchEvent.h"
#include "../Transform.h"
#include "../Sequences/SequenceBase.h"
#include "../Sequences/BeginningSequence.h"
#include "../Sequences/ExplosionsSequence.h"
#include "../Sequences/MagnetSequence.h"
#include "../Sequences/EndlessFlightSequence.h"
#include "../Sequences/OutroSequence.h"
#include "../FuturisEngine/Screen.h"
#include "Graphics/Texture.h"
#include "Graphics/Material.h"
#include "Graphics/Content/Content.h"
#include <Utils/Random.h>
#include <UserInput/Input.h>

bool StopBlink;

void FadeOut(float speed, bool white);

sm::Vec3 ColorBlue = sm::Vec3(20.0f / 256.0f, 160.0f / 256.0f, 1);
sm::Vec3 ColorOrange = sm::Vec3(188.0f / 256.0f, 81.0f / 256.0f, 0);
sm::Vec3 ColorGreen = sm::Vec3(43.0f / 256.0f, 191.0f / 256.0f, 17.0f / 256.0f);
Material* GlowMaterial;
int CurrentColor;

void SetSphereColor(int index)
{
	CurrentColor = index;
	CurrentColor %= 3;

	sm::Vec3 colors[] =
	{
		ColorBlue,
		ColorGreen,
		ColorOrange
	};

	GlowMaterial->SetParameter("u_color", colors[CurrentColor]);

	StopBlink = true;
}

void SetNextSphereColor()
{
	SetSphereColor(CurrentColor + 1);
}

SceneController::SceneController(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_currentSequence(nullptr),
	m_beginningSequence(nullptr),
	m_explosionsSequence(nullptr),
	m_magnetSequence(nullptr),
	m_endlessFlightSequence(nullptr),
	m_outroSequence(nullptr),
	m_renderTarget(nullptr),
	m_renderTargetGlow(nullptr)
{
}

void SceneController::Awake()
{
	SynchManager::GetInstance()->RegisterObserver(this);

	m_spherePrefab = ScenesManager::GetInstance()->FindGameObject("Sphere");
	m_spherePrefab->SetActive(false);
//	m_spherePrefab->SetLayerId(LayerId_1, true);

	m_mechArmPrefab = ScenesManager::GetInstance()->FindGameObject("MechArm");
	m_mechArmPrefab->SetActive(false);
//	m_mechArmPrefab->SetLayerId(LayerId_1, true);

	m_commonSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab)->GetComponent("Sphere"));
	m_commonSphere->Initialize(m_mechArmPrefab);
	m_commonSphere->GetGameObject()->SetActive(false);

	m_mainCamera = (MainCamera*)ScenesManager::GetInstance()->FindGameObject("MainCamera")->GetComponent("MainCamera");

	m_renderTarget = new Texture(
		Screen::Width,
		Screen::Height,
		32,
		NULL,
		BaseTexture::Wrap_ClampToEdge,
		BaseTexture::Filter_Linear,
		BaseTexture::Filter_Linear,
		false);

	m_renderTargetGlow = new Texture(
		Screen::Width,
		Screen::Height,
		32,
		NULL,
		BaseTexture::Wrap_ClampToEdge,
		BaseTexture::Filter_Linear,
		BaseTexture::Filter_Linear,
		false);

	m_mainCamera->GetCamera()->SetRenderToTexture(m_renderTarget, m_renderTargetGlow, nullptr);

	m_beginningSequence = new BeginningSequence(m_commonSphere, m_mainCamera);
	m_beginningSequence->Initialize();

	m_magnetSequence = new MagnetSequence(m_commonSphere, m_mainCamera);
	m_magnetSequence->Initialize();

	m_explosionsSequence = new ExplosionsSequence(m_spherePrefab, m_mechArmPrefab, m_mainCamera);
	m_explosionsSequence->Initialize();

	m_endlessFlightSequence = new EndlessFlightSequence(m_spherePrefab, m_mechArmPrefab, m_mainCamera);
	m_endlessFlightSequence->Initialize();

	m_outroSequence = new OutroSequence(m_commonSphere, m_mainCamera);
	m_outroSequence->Initialize();

	BackCamera* backCamera = dynamic_cast<BackCamera*>(ScenesManager::GetInstance()->FindGameObject("BackCamera")->GetComponent("BackCamera"));
	backCamera->Initialize(m_mainCamera, m_spherePrefab);

	GlowMaterial = Content::Instance->Get<Material>("glow");
}

void SceneController::Update()
{
	if (Input::GetKeyDown(KeyCode_L))
	{
		SetNextSphereColor();
	}

	if (m_currentSequence != nullptr)
		m_currentSequence->Update();
}

Texture* SceneController::GetRenderTarget() const
{
	return m_renderTarget;
}

Texture* SceneController::GetRenderTargetGlow() const
{
	return m_renderTargetGlow;
}

void SceneController::SynchEventFired(SynchEvent* synchEvent)
{
	if (synchEvent->GetId() == "prepare_for_beginning")
	{
		ChangeSequence(m_beginningSequence);
	}
	else if (synchEvent->GetId() == "prepare_for_magnet")
	{
		ChangeSequence(m_magnetSequence);
	}
	else if (synchEvent->GetId() == "prepare_for_explosions")
	{
		ChangeSequence(m_explosionsSequence);
	}
	else if (synchEvent->GetId() == "endless_flight")
	{
		ChangeSequence(m_endlessFlightSequence);
	}
	else if (synchEvent->GetId() == "prepare_for_outro")
	{
		ChangeSequence(m_outroSequence);
	}
	else if (synchEvent->GetId() == "color_blue")
	{
		SetSphereColor(0);
		
	}
	else if (synchEvent->GetId() == "color_green")
	{
		SetSphereColor(1);
	}
	else if (synchEvent->GetId() == "color_orange")
	{
		SetSphereColor(2);
	}
	else if (synchEvent->GetId() == "flash")
	{
		FadeOut(1.0f / 2.0f, true);
	}

	if (m_currentSequence != nullptr)
		m_currentSequence->NotifySynchEvent(synchEvent);
}

void SceneController::ChangeSequence(SequenceBase* sequence)
{
	if (m_currentSequence != nullptr)
		m_currentSequence->Clean();

	m_currentSequence = sequence;
	m_currentSequence->Prepare();
}
