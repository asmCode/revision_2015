#include "ExplosionsSequence.h"
#include "../Behaviours/Sphere.h"
#include "../Behaviours/SpherePart.h"
#include "../Behaviours/SpherePartCommands/PullOut.h"
#include "../Behaviours/SpherePartCommands/PullIn.h"
#include "../Behaviours/SpherePartCommands/SlideOut.h"
#include "../Behaviours/MainCamera.h"
#include "../FuturisEngine/Animation/Animation.h"
#include "../Transform.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Camera.h"
#include "../SynchEvent.h"
#include "../FuturisEngine/Time.h"
#include "../Behaviours/SpherePartCommands/Explode.h"
#include "../Behaviours/SpherePartCommands/Reset.h"
#include <UserInput/Input.h>
#include <Utils/Log.h>
#include <Math/MathUtils.h>
#include <Math/Animation/LinearCurve.h>

bool m_isBreaking;
float m_speedBase;
float m_breakTime;

ExplosionsSequence::ExplosionsSequence(GameObject* spherePrefab, GameObject* m_mechArmPrefab, MainCamera* mainCamera) :
m_spherePrefab(spherePrefab),
m_mechArmPrefab(m_mechArmPrefab),
m_mainCamera(mainCamera),
m_speed(0.0f)
{

}

void ExplosionsSequence::Initialize()
{
	m_normalSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab)->GetComponent("Sphere"));
	m_normalSphere->Initialize(nullptr);
	m_normalSphere->GetGameObject()->SetActive(false);

	m_smallSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab)->GetComponent("Sphere"));
	m_smallSphere->Initialize(nullptr);
	m_smallSphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(0.1f, 0.1f, 0.1f));
	m_smallSphere->GetGameObject()->SetActive(false);
}

void ExplosionsSequence::Update()
{
	if (m_isBreaking)
	{
		m_breakTime += Time::DeltaTime;

		LinearCurve<float> curve;
		m_speed = curve.Evaluate(m_speedBase, 0.0f, m_breakTime / 1.8f);
	}

	sm::Vec3 position = m_mainCamera->GetGameObject()->GetTransform().GetLocalPosition();
	position.z -= Time::DeltaTime * m_speed;
	m_mainCamera->GetGameObject()->GetTransform().SetLocalPosition(position);

	/*
	if (Input::GetKeyDown(KeyCode_S))
		SwapSpheres();

	if (Input::GetKeyDown(KeyCode_E))
		ExplodeSphere();
	*/
}

void ExplosionsSequence::Prepare()
{
	m_mainCamera->GetGameObject()->GetTransform().SetParent(&m_smallSphere->GetGameObject()->GetTransform());
	m_mainCamera->ClearCommands();
	m_mainCamera->GetCamera()->SetFov(90.0f * MathUtils::Deg2Rad);
	m_mainCamera->EnableSmoothNoise(true);
	m_mainCamera->GetAnimation()->Stop();

	Transform* cameraTransform = &ScenesManager::GetInstance()->FindGameObject("InitialExplosionCameraPosition")->GetTransform();

	m_mainCamera->GetGameObject()->GetTransform().SetLocalPosition(cameraTransform->GetPosition());
	m_mainCamera->GetGameObject()->GetTransform().SetLocalRotation(cameraTransform->GetRotation());
	m_mainCamera->GetGameObject()->GetTransform().SetLocalScale(cameraTransform->GetLocalScale());

	m_normalSphere->GetGameObject()->SetActive(false);
	m_smallSphere->GetGameObject()->SetActive(true);

	float distance = m_mainCamera->GetGameObject()->GetTransform().GetLocalPosition().z - 2.0f;
	m_speed = distance / 1.379f;
	//m_speed = 0.0f;
}

void ExplosionsSequence::Clean()
{
	m_normalSphere->GetGameObject()->SetActive(false);
	m_smallSphere->GetGameObject()->SetActive(false);
}

void ExplosionsSequence::ExplodeSphere(Sphere* sphere)
{
	const std::vector<SpherePart*>& parts = sphere->GetSphereParts();
	for (uint32_t i = 0; i < parts.size(); i++)
	{
		Explode* command = new Explode();
		parts[i]->SetCommand(command);
	}
}

void ExplosionsSequence::SwapSpheres()
{
	m_mainCamera->GetGameObject()->GetTransform().SetParent(&m_smallSphere->GetGameObject()->GetTransform());
	m_smallSphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(1, 1, 1));
	m_normalSphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(0.1f, 0.1f, 0.1f));

	Sphere* tmp = m_smallSphere;
	m_smallSphere = m_normalSphere;
	m_normalSphere = tmp;
}

void ExplosionsSequence::ResetSphere(Sphere* sphere)
{
	const std::vector<SpherePart*>& parts = sphere->GetSphereParts();
	for (uint32_t i = 0; i < parts.size(); i++)
	{
		Reset* command = new Reset();
		parts[i]->SetCommand(command);
	}
}

void ExplosionsSequence::Repeat()
{
	m_normalSphere->GetGameObject()->SetActive(true);
	m_smallSphere->GetGameObject()->SetActive(true);

	ExplodeSphere(m_smallSphere);
	ResetSphere(m_normalSphere);
	SwapSpheres();

	float distance = m_mainCamera->GetGameObject()->GetTransform().GetLocalPosition().z - 2.0f;
	m_speed = distance / 1.379f;
}

void ExplosionsSequence::NotifySynchEvent(SynchEvent* synchEvent)
{
	if (synchEvent->GetId() == "explode")
	{
		Repeat();
	}
	else if (synchEvent->GetId() == "break")
	{
		m_isBreaking = true;
		m_speedBase = m_speed;
		m_mainCamera->EnableSmoothNoise(false);
	}
	else if (synchEvent->GetId() == "open_gate")
	{
		SpherePart* dd = m_smallSphere->GetClosestPart(m_mainCamera->GetRootTransform()->GetPosition());
		dd->QueueCommand(new PullOut(0.4f, 0.5f));
		dd->QueueCommand(new SlideOut(0.8f, 0.6f, sm::Vec3(1, 0, 0)));
	}
}
