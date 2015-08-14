#include "ExplosionsSequence.h"
#include "Sphere.h"
#include "SpherePart.h"
#include "../Transform.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Camera.h"
#include "../FuturisEngine/Time.h"
#include "SpherePartCommands/Explode.h"
#include "SpherePartCommands/Reset.h"
#include <UserInput/Input.h>
#include <Utils/Log.h>

ExplosionsSequence::ExplosionsSequence(Sphere* spherePrefab, GameObject* m_mechArmPrefab, Camera* mainCamera) :
m_spherePrefab(spherePrefab),
m_mechArmPrefab(m_mechArmPrefab),
m_mainCamera(mainCamera),
m_speed(0.0f)
{

}

void ExplosionsSequence::Initialize()
{
	m_normalSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab->GetGameObject())->GetComponent("Sphere"));
	m_normalSphere->Initialize(nullptr);

	m_smallSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab->GetGameObject())->GetComponent("Sphere"));
	m_smallSphere->Initialize(nullptr);
	m_smallSphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(0.1f, 0.1f, 0.1f));
}

void ExplosionsSequence::Update()
{
	const float explodeDistance = 20.0f;

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

	Transform* cameraTransform = &ScenesManager::GetInstance()->FindGameObject("InitialExplosionCameraPosition")->GetTransform();

	m_mainCamera->GetGameObject()->GetTransform().SetLocalPosition(cameraTransform->GetPosition());
	m_mainCamera->GetGameObject()->GetTransform().SetLocalRotation(cameraTransform->GetRotation());
	m_mainCamera->GetGameObject()->GetTransform().SetLocalScale(cameraTransform->GetLocalScale());

	m_normalSphere->GetGameObject()->SetActive(false);

	float distance = m_mainCamera->GetGameObject()->GetTransform().GetLocalPosition().z - 6.0f;
	//m_speed = distance / 1.379f;
	m_speed = 0.0f;
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

	float distance = m_mainCamera->GetGameObject()->GetTransform().GetLocalPosition().z - 6.0f;
	m_speed = distance / 1.379f;
}
