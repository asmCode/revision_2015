#include "BackCamera.h"
#include "../Camera.h"
#include "Sphere.h"
#include "SpherePart.h"
#include "MainCamera.h"
#include "SmoothNoise.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../FuturisEngine/Time.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include <Math/MathUtils.h>

BackCamera::BackCamera(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_mainCamera(nullptr),
	m_spherePrefab(nullptr)
{
}

void BackCamera::Initialize(MainCamera* mainCamera, GameObject* spherePrefab)
{
	m_mainCamera = mainCamera;
	m_spherePrefab = spherePrefab;
}

void BackCamera::Awake()
{
	m_sphere1 = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab)->GetComponent("Sphere"));
	m_sphere1->GetGameObject()->SetLayerId(LayerId_2, true);
	m_sphere1->Initialize(nullptr);
	m_sphere2 = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab)->GetComponent("Sphere"));
	m_sphere2->Initialize(nullptr);
	m_sphere2->GetGameObject()->SetLayerId(LayerId_2, true);

	PrepareBg();
}

void BackCamera::Update()
{
	GetGameObject()->GetTransform().SetRotation(m_mainCamera->GetCamera()->GetGameObject()->GetTransform().GetRotation());
}

void BackCamera::PrepareBg()
{
	PrepareSphere(m_sphere1, 1.0, 2.0f, MathUtils::PI);
	PrepareSphere(m_sphere2, 2.0, 1.0f, 0.2f);
}

void BackCamera::PrepareSphere(Sphere* sphere, float scale, float dist, float angle)
{
	sphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(scale, scale, scale));

	const std::vector<SpherePart*>& parts = sphere->GetSphereParts();
	for (size_t i = 0; i < parts.size(); i++)
	{
		sm::Vec3 localPos = parts[i]->GetGameObject()->GetTransform().GetLocalPosition();
		parts[i]->GetGameObject()->GetTransform().SetLocalPosition(localPos + localPos.GetNormalized() * dist);

		SmoothNoise* noise = dynamic_cast<SmoothNoise*>(parts[i]->GetGameObject()->AddComponent("SmoothNoise"));
		noise->RotationNoise(0.1f, angle);
	}
}
