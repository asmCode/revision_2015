#include "BeginningSequence.h"
#include "../GameObject.h"
#include "../Behaviours/Sphere.h"
#include "../Behaviours/SpherePart.h"
#include "../Behaviours/Noise.h"
#include "../Behaviours/SpherePartCommands/PullOut.h"
#include "../Behaviours/SpherePartCommands/PullIn.h"
#include "../Camera.h"
#include "../Transform.h"
#include "../SynchEvent.h"
#include "../FuturisEngine/Time.h"
#include <Utils/Random.h>
#include <UserInput/Input.h>

BeginningSequence::BeginningSequence(Sphere* sphere, Camera* mainCamera):
m_sphere(sphere),
m_mainCamera(mainCamera),
m_pullOutLongBaseIndex(0)
{
	m_cameraPivot = new GameObject("CameraPivot");

	m_mainCamera->GetGameObject()->GetTransform().SetParent(&m_cameraPivot->GetTransform());
	m_cameraAngle = 0.0f;

	//m_cameraPivot->GetTransform().SetRotation(sm::Quat::FromAngleAxis(1.0f, sm::Vec3(1, 0, 0)));
}

void BeginningSequence::Initialize()
{
}

Noise* noise;

void BeginningSequence::Prepare()
{
	m_mainCamera->GetGameObject()->GetTransform().SetPosition(sm::Vec3(0, 0, 40));
	m_sphere->GetGameObject()->SetActive(true);
	//noise = (Noise*)m_sphere->GetGameObject()->AddComponent("Noise");
	//noise->TranslationNoise(20.0f, 0.5f);
	//noise->RotationNoise(1.0f, 0.05f);
}

void BeginningSequence::Clean()
{
	m_sphere->GetGameObject()->SetActive(false);
}

int index = 0;

void BeginningSequence::Update()
{
	/*
	m_cameraAngle += Time::DeltaTime * 0.3f;

	m_cameraPivot->GetTransform().SetRotation(
		sm::Quat::FromAngleAxis(m_cameraAngle, sm::Vec3(0, 1, 0)) *
		sm::Quat::FromAngleAxis(0.4f, sm::Vec3(1, 0, 0)));
		*/

	if (Input::GetKeyDown(KeyCode::KeyCode_Space))
	{
		PullOutLong();
	}
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
	else if (synchEvent->GetId() == "pull_put_long")
	{
		PullOutLong();
	}
}

void BeginningSequence::PullOutLong()
{
	const std::vector<SpherePart*>& parts = m_sphere->GetSphereParts();
	const int groups = 3;

	for (size_t i = 0; i < parts.size(); i++)
	{
		if (i % groups == m_pullOutLongBaseIndex)
			m_sphere->GetSphereParts()[i]->QueueCommand(new PullOut(0.3f, 6.0f));
		else
			m_sphere->GetSphereParts()[i]->QueueCommand(new PullIn(0.3f));
	}

	m_pullOutLongBaseIndex++;
	m_pullOutLongBaseIndex %= groups;
}
