#include "EndlessFlightSequence.h"
#include "../Behaviours/Sphere.h"
#include "../Behaviours/SpherePart.h"
#include "../Transform.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Camera.h"
#include "../SynchEvent.h"
#include "../../DebugUtils.h"
#include "../FuturisEngine/Time.h"
#include "../Behaviours/SpherePartCommands/Explode.h"
#include "../Behaviours/SpherePartCommands/Reset.h"
#include <UserInput/Input.h>
#include <Utils/Log.h>
#include <Utils/Random.h>

EndlessFlightSequence::EndlessFlightSequence(GameObject* spherePrefab, GameObject* m_mechArmPrefab, Camera* mainCamera) :
m_spherePrefab(spherePrefab),
m_mechArmPrefab(m_mechArmPrefab),
m_mainCamera(mainCamera),
m_speed(0.0f),
m_cameraCurve(nullptr)
{

}

void EndlessFlightSequence::Initialize()
{
	m_normalSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab)->GetComponent("Sphere"));
	m_normalSphere->Initialize(nullptr);
	m_normalSphere->GetGameObject()->SetActive(false);

	m_smallSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab)->GetComponent("Sphere"));
	m_smallSphere->Initialize(nullptr);
	m_smallSphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(0.1f, 0.1f, 0.1f));
	m_smallSphere->GetGameObject()->SetActive(false);
}

void EndlessFlightSequence::Update()
{
	const float explodeDistance = 20.0f;

	sm::Vec3 position = m_mainCamera->GetGameObject()->GetTransform().GetLocalPosition();
	position.z -= Time::DeltaTime * m_speed;
	m_mainCamera->GetGameObject()->GetTransform().SetLocalPosition(position);

	if (Input::GetKeyDown(KeyCode_Space))
		Repeat();

	if (m_cameraCurve != nullptr)
		DebugUtils::DrawCurve(*m_cameraCurve, 0.1f, sm::Vec3(1, 0, 0));
}

void EndlessFlightSequence::Prepare()
{
	/*
	m_mainCamera->GetGameObject()->GetTransform().SetParent(&m_smallSphere->GetGameObject()->GetTransform());

	Transform* cameraTransform = &ScenesManager::GetInstance()->FindGameObject("InitialExplosionCameraPosition")->GetTransform();

	m_mainCamera->GetGameObject()->GetTransform().SetLocalPosition(cameraTransform->GetPosition());
	m_mainCamera->GetGameObject()->GetTransform().SetLocalRotation(cameraTransform->GetRotation());
	m_mainCamera->GetGameObject()->GetTransform().SetLocalScale(cameraTransform->GetLocalScale());*/

	m_normalSphere->GetGameObject()->SetActive(true);
	m_smallSphere->GetGameObject()->SetActive(true);

	/*float distance = m_mainCamera->GetGameObject()->GetTransform().GetLocalPosition().z - 6.0f;
	//m_speed = distance / 1.379f;
	m_speed = 0.0f;
	*/
}

void EndlessFlightSequence::Clean()
{

}

void EndlessFlightSequence::ExplodeSphere(Sphere* sphere)
{
	const std::vector<SpherePart*>& parts = sphere->GetSphereParts();
	for (uint32_t i = 0; i < parts.size(); i++)
	{
		Explode* command = new Explode();
		parts[i]->SetCommand(command);
	}
}

void EndlessFlightSequence::SwapSpheres()
{
	m_mainCamera->GetGameObject()->GetTransform().SetParent(&m_smallSphere->GetGameObject()->GetTransform());
	m_smallSphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(1, 1, 1));
	m_normalSphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(0.1f, 0.1f, 0.1f));

	Sphere* tmp = m_smallSphere;
	m_smallSphere = m_normalSphere;
	m_normalSphere = tmp;
}

void EndlessFlightSequence::ResetSphere(Sphere* sphere)
{
	const std::vector<SpherePart*>& parts = sphere->GetSphereParts();
	for (uint32_t i = 0; i < parts.size(); i++)
	{
		Reset* command = new Reset();
		parts[i]->SetCommand(command);
	}
}

void EndlessFlightSequence::Repeat()
{
	SpherePart* part = GetRandomPart(m_smallSphere);
	m_cameraCurve = CreateCurve(
		m_mainCamera->GetGameObject()->GetTransform().GetPosition(),
		part->GetGameObject()->GetTransform().GetPosition(),
		m_smallSphere->GetGameObject()->GetTransform().GetPosition());

	/*
	m_normalSphere->GetGameObject()->SetActive(true);
	m_smallSphere->GetGameObject()->SetActive(true);

	ExplodeSphere(m_smallSphere);
	ResetSphere(m_normalSphere);
	SwapSpheres();

	float distance = m_mainCamera->GetGameObject()->GetTransform().GetLocalPosition().z - 6.0f;
	m_speed = distance / 1.379f;
	*/
}

void EndlessFlightSequence::NotifySynchEvent(SynchEvent* synchEvent)
{
}

SpherePart* EndlessFlightSequence::GetRandomPart(Sphere* sphere)
{
	return sphere->GetSphereParts()[Random::GetInt(0, sphere->GetSphereParts().size() - 1)];
}

AnimationCurve<sm::Vec3>* EndlessFlightSequence::CreateCurve(const sm::Vec3& start, const sm::Vec3& end, const sm::Vec3& pivot)
{
	AnimationCurve<sm::Vec3>* curve = new AnimationCurve<sm::Vec3>();

	curve->AddKeyframe(0.0f, start);
	curve->AddKeyframe(1.0f, end);

	return curve;
}
