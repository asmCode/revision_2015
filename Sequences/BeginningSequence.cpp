#include "BeginningSequence.h"
#include "../GameObject.h"
#include "../Behaviours/Sphere.h"
#include "../Camera.h"
#include "../Transform.h"
#include "../SynchEvent.h"
#include "../FuturisEngine/Time.h"
#include <Utils/Random.h>


BeginningSequence::BeginningSequence(GameObject* spherePrefab, GameObject* mechArmPrefab, Camera* mainCamera):
m_spherePrefab(spherePrefab),
m_mechArmPrefab(mechArmPrefab),
m_mainCamera(mainCamera),
m_sphere(nullptr)
{
	m_cameraPivot = new GameObject("CameraPivot");

	m_mainCamera->GetGameObject()->GetTransform().SetParent(&m_cameraPivot->GetTransform());
	m_cameraAngle = 0.0f;

	//m_cameraPivot->GetTransform().SetRotation(sm::Quat::FromAngleAxis(1.0f, sm::Vec3(1, 0, 0)));
}

void BeginningSequence::Initialize()
{
	m_sphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab)->GetComponent("Sphere"));
	m_sphere->Initialize(m_mechArmPrefab);
	m_sphere->GetGameObject()->SetActive(false);
}

void BeginningSequence::Prepare()
{
	m_mainCamera->GetGameObject()->GetTransform().SetPosition(sm::Vec3(0, 0, 40));
	m_sphere->GetGameObject()->SetActive(true);
}

void BeginningSequence::Clean()
{
	m_sphere->GetGameObject()->SetActive(false);
}

void BeginningSequence::Update()
{
	m_cameraAngle += Time::DeltaTime * 0.3f;

	m_cameraPivot->GetTransform().SetRotation(
		sm::Quat::FromAngleAxis(m_cameraAngle, sm::Vec3(0, 1, 0)) *
		sm::Quat::FromAngleAxis(0.4f, sm::Vec3(1, 0, 0)));
}

void BeginningSequence::NotifySynchEvent(SynchEvent* synchEvent)
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
}
