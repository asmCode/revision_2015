#include "SceneController.h"
#include "Sphere.h"
#include "../Camera.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../SynchManager.h"
#include "../SynchEvent.h"
#include "../Transform.h"
#include "../Sequences/ExplosionsSequence.h"
#include <Utils/Random.h>
#include <UserInput/Input.h>

SceneController::SceneController(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_explosionsSequence(nullptr)
{
}

void SceneController::Awake()
{
	SynchManager::GetInstance()->RegisterObserver(this);

	m_spherePrefab = (Sphere*)ScenesManager::GetInstance()->FindGameObject("Sphere")->GetComponent("Sphere");
	m_spherePrefab->GetGameObject()->SetActive(false);

	m_mechArmPrefab = ScenesManager::GetInstance()->FindGameObject("MechArm");
	m_mechArmPrefab->SetActive(false);

	m_mainCamera = (Camera*)ScenesManager::GetInstance()->FindGameObject("MainCamera")->GetComponent("Camera");
}

void SceneController::Update()
{
	if (Input::GetKeyDown(KeyCode_L))
	{
	}

	if (m_explosionsSequence != nullptr)
		m_explosionsSequence->Update();
}

void SceneController::SynchEventFired(SynchEvent* synchEvent)
{
	if (synchEvent->GetId() == "blink1")
	{
		const int totalCount = 54;
		const int subCount = 20;

		int elements[totalCount];
		Random::GetRandomUniqueArray(elements, 0, totalCount - 1);

		for (int i = 0; i < subCount; i++)
			m_sphere->BlinkSpherePart(elements[i], sm::Vec3(0.9f, 0.9f, 0.9f));
	}
	else if (synchEvent->GetId() == "beat1")
	{
		const int totalCount = 54;
		const int subCount = 20;

		int elements[totalCount];
		Random::GetRandomUniqueArray(elements, 0, totalCount - 1);

		for (int i = 0; i < subCount; i++)
			m_sphere->RollSpherePart(elements[i]);
	}
	else if (synchEvent->GetId() == "open_mech1")
	{
		m_sphere->OpenWithMechArms();
	}
	else if (synchEvent->GetId() == "prepare_for_explosions")
	{
		PrepareForExplosions();
	}
	else if (synchEvent->GetId() == "explode")
	{
		m_explosionsSequence->Repeat();
	}
	else if (synchEvent->GetId() == "prepare_for_beginning")
	{
		PrepareForBeginning();
	}
	
}

void SceneController::PrepareForExplosions()
{
	m_explosionsSequence = new ExplosionsSequence(m_spherePrefab, m_mechArmPrefab, m_mainCamera);
	m_explosionsSequence->Initialize();
	m_explosionsSequence->Prepare();
}

void SceneController::PrepareForBeginning()
{
	m_explosionsSequence = new ExplosionsSequence(m_spherePrefab, m_mechArmPrefab, m_mainCamera);
	m_explosionsSequence->Initialize();
	m_explosionsSequence->Prepare();
}
