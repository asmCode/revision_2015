#include "SceneController.h"
#include "Sphere.h"
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
#include <Utils/Random.h>
#include <UserInput/Input.h>

void FadeOut(float speed, bool white);

SceneController::SceneController(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_currentSequence(nullptr),
	m_beginningSequence(nullptr),
	m_explosionsSequence(nullptr),
	m_magnetSequence(nullptr),
	m_endlessFlightSequence(nullptr),
	m_outroSequence(nullptr)
{
}

void SceneController::Awake()
{
	SynchManager::GetInstance()->RegisterObserver(this);

	m_spherePrefab = ScenesManager::GetInstance()->FindGameObject("Sphere");
	m_spherePrefab->SetActive(false);

	m_mechArmPrefab = ScenesManager::GetInstance()->FindGameObject("MechArm");
	m_mechArmPrefab->SetActive(false);

	m_commonSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab)->GetComponent("Sphere"));
	m_commonSphere->Initialize(m_mechArmPrefab);
	m_commonSphere->GetGameObject()->SetActive(false);

	m_mainCamera = (MainCamera*)ScenesManager::GetInstance()->FindGameObject("MainCamera")->GetComponent("MainCamera");

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
}

void SceneController::Update()
{
	if (Input::GetKeyDown(KeyCode_L))
	{
	}

	if (m_currentSequence != nullptr)
		m_currentSequence->Update();
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
