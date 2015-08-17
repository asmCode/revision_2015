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
#include <Utils/Random.h>
#include <UserInput/Input.h>

SceneController::SceneController(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_currentSequence(nullptr),
	m_beginningSequence(nullptr),
	m_explosionsSequence(nullptr),
	m_magnetSequence(nullptr)
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

	m_mainCamera = (Camera*)ScenesManager::GetInstance()->FindGameObject("MainCamera")->GetComponent("Camera");

	m_beginningSequence = new BeginningSequence(m_commonSphere, m_mainCamera);
	m_beginningSequence->Initialize();

	m_magnetSequence = new MagnetSequence(m_commonSphere, m_mainCamera);
	m_magnetSequence->Initialize();

	m_explosionsSequence = new ExplosionsSequence(m_spherePrefab, m_mechArmPrefab, m_mainCamera);
	m_explosionsSequence->Initialize();
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
	else if (synchEvent->GetId() == "prepare_for_explosions")
	{
		ChangeSequence(m_explosionsSequence);
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
