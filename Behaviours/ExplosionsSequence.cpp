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

ExplosionsSequence::ExplosionsSequence(Sphere* spherePrefab, GameObject* m_mechArmPrefab, Camera* mainCamera) :
m_spherePrefab(spherePrefab),
m_mechArmPrefab(m_mechArmPrefab),
m_mainCamera(mainCamera)
{

}

void ExplosionsSequence::Initialize()
{
	m_normalSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab->GetGameObject())->GetComponent("Sphere"));
	m_normalSphere->Initialize(nullptr);

	m_smallSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab->GetGameObject())->GetComponent("Sphere"));
	m_smallSphere->Initialize(nullptr);
	m_smallSphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(0.02f, 0.02f, 0.02f));
}

void ExplosionsSequence::Prepare()
{
	Transform* cameraTransform = &ScenesManager::GetInstance()->FindGameObject("InitialExplosionCameraPosition")->GetTransform();

	m_mainCamera->GetGameObject()->GetTransform().SetPosition(cameraTransform->GetPosition());
	m_mainCamera->GetGameObject()->GetTransform().SetRotation(cameraTransform->GetRotation());
	m_mainCamera->GetGameObject()->GetTransform().SetLocalScale(cameraTransform->GetLocalScale());
}

void ExplosionsSequence::Update()
{
	sm::Vec3 position = m_mainCamera->GetGameObject()->GetTransform().GetLocalPosition();
	position.z -= Time::DeltaTime * position.GetLength() * 0.5f;
	m_mainCamera->GetGameObject()->GetTransform().SetLocalPosition(position);

	if (Input::GetKeyDown(KeyCode_S))
		SwapSpheres();

	if (Input::GetKeyDown(KeyCode_E))
		ExplodeSphere();
}

void ExplosionsSequence::ExplodeSphere()
{
	const std::vector<SpherePart*>& parts = m_normalSphere->GetSphereParts();
	for (uint32_t i = 0; i < parts.size(); i++)
	{
		Explode* command = new Explode();
		parts[i]->QueueCommand(command);
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

	ResetSphere(m_smallSphere);
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
