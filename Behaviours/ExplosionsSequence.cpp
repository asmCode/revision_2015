#include "ExplosionsSequence.h"
#include "Sphere.h"
#include "../Transform.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Camera.h"
#include "../FuturisEngine/Time.h"

ExplosionsSequence::ExplosionsSequence(Sphere* spherePrefab, Camera* mainCamera) :
m_spherePrefab(spherePrefab),
m_mainCamera(mainCamera)
{
}

void ExplosionsSequence::Initialize()
{
	m_normalSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab->GetGameObject())->GetComponent("Sphere"));
	m_smallSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab->GetGameObject())->GetComponent("Sphere"));

	m_smallSphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(0.1f, 0.1f, 0.1f));
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
	position.z -= Time::DeltaTime * 10.0f;
	m_mainCamera->GetGameObject()->GetTransform().SetLocalPosition(position);
}

void ExplosionsSequence::SwapSpheres()
{

}
