#include "SceneController.h"
#include "Sphere.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../SynchManager.h"
#include "../SynchEvent.h"
#include <Utils/Random.h>
#include <UserInput/Input.h>

SceneController::SceneController(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void SceneController::Awake()
{
	SynchManager::GetInstance()->RegisterObserver(this);

	m_sphere = (Sphere*)ScenesManager::GetInstance()->FindGameObject("Sphere")->GetComponent("Sphere");
}

void SceneController::Update()
{
	if (Input::GetKeyDown(KeyCode_L))
	{
	}
}

void SceneController::SynchEventFired(SynchEvent* synchEvent)
{
	if (synchEvent->GetId() == "beat1")
	{
		const int totalCount = 54;
		const int subCount = 20;

		int elements[totalCount];
		Random::GetRandomUniqueArray(elements, 0, totalCount - 1);

		for (int i = 0; i < subCount; i++)
			m_sphere->RollSpherePart(elements[i]);
	}
}

