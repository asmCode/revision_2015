#include "Sphere.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../Camera.h"
#include "../Renderable.h"
#include "../FuturisEngine/Graphics/Mesh.h"
#include "SpherePart.h"
#include "MechArm.h"
#include "SpherePartCommands/PullOut.h"
#include "SpherePartCommands/PullIn.h"
#include "SpherePartCommands/SlideOut.h"
#include "SpherePartCommands/SlideIn.h"
#include "SpherePartCommands/RollOut.h"
#include "SpherePartCommands/RollIn.h"
#include "SpherePartCommands/Blink.h"
#include "SpherePartCommands/PullOutWithNoise.h"
#include "../DemoUtils.h"
#include <Graphics/Material.h>
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Utils/Random.h>
#include <Utils/Log.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"
#include <algorithm>

using namespace FuturisEngine::Graphics;

Sphere::Sphere(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void Sphere::Awake()
{
}

void Sphere::Initialize(GameObject* mechArmPrefab)
{
	std::vector<GameObject*> spherePartsGameObjects;
	DemoUtils::GetAllChildrenWitchPrefix(GetGameObject(), "SpherePart", spherePartsGameObjects);
	DemoUtils::AttachComponentBunch<SpherePart>("SpherePart", spherePartsGameObjects, m_parts);

	SortSphereParts();

	Material* commonMaterial = m_parts[0]->GetGameObject()->GetRenderables()[0]->GetMaterial();

	for (uint32_t i = 0; i < m_parts.size(); i++)
	{
		Material* material = new Material();
		material->SetShader(commonMaterial->GetShader());
		material->SetParameter("u_color", commonMaterial->GetParameterVec3("u_color"));
		material->SetParameter("u_glossiness", commonMaterial->GetParameterFloat("u_glossiness"));
		material->SetParameter("u_specularLevel", commonMaterial->GetParameterFloat("u_specularLevel"));

		m_parts[i]->GetGameObject()->GetRenderables()[0]->SetMaterial(material);
	}

	if (mechArmPrefab != nullptr)
		CreateMechArms(mechArmPrefab);
}

void Sphere::RollSpherePart(int index)
{
	//int index = Random::GetInt(0, m_parts.size() - 1);
	//int index = 33;

	PullOut* pullOut = new PullOut(0.32f, 1.2f);
	m_parts[index]->QueueCommand(pullOut);

	/*
	SlideOut* slideOut = new SlideOut(0.5f, MathUtils::PI / 6.0f, sm::Vec3(1, 0, 0));
	m_parts[index]->QueueCommand(slideOut);

	SlideIn* slideIn = new SlideIn(0.5f);
	m_parts[index]->QueueCommand(slideIn);
	*/

	RollOut* rollOut = new RollOut(0.32f, MathUtils::PI2 - 0.01f);
	m_parts[index]->QueueCommand(rollOut);

	RollIn* rollIn = new RollIn(0.32f);
	m_parts[index]->QueueCommand(rollIn);

	PullIn* pullIn = new PullIn(0.32f);
	m_parts[index]->QueueCommand(pullIn);
}

void Sphere::BlinkSpherePart(int index, const sm::Vec3& color)
{
	Blink* blink = new Blink(0.5f, color);
	m_parts[index]->QueueCommand(blink);
}

void Sphere::OpenWithMechArms()
{
	for (uint32_t i = 0; i < m_parts.size(); i++)
	{
		PullOutWithNoise* pullOutWithNoise = new PullOutWithNoise(0.32f, 1.4f);
		m_parts[i]->QueueCommand(pullOutWithNoise);
	}
}

void Sphere::ShowMechArms(bool show)
{
	for (size_t i = 0; i < m_mechArms.size(); i++)
		m_mechArms[i]->GetGameObject()->SetActive(show);
}

const std::vector<SpherePart*>& Sphere::GetSphereParts() const
{
	return m_parts;
}

float angle;

void Sphere::Update()
{
	if (m_mechArms.size() > 0)
	{
		for (uint32_t i = 0; i < m_parts.size(); i++)
		{
			m_mechArms[i]->SetTarget(m_parts[i]->GetGameObject()->GetTransform().GetPosition());
		}
	}

	/*angle += Time::DeltaTime * 0.4f;

	GetGameObject()->GetTransform().SetLocalRotation(
		sm::Quat::FromAngleAxis(MathUtils::PI / -6, sm::Vec3(1, 0, 0)) *
		sm::Quat::FromAngleAxis(angle, sm::Vec3(0, 1, 0)));
	GetGameObject()->GetTransform().SetLocalPosition(sm::Vec3(0, 0, -45));
	*/

	if (Input::GetKeyDown(KeyCode_O))
	{
		Renderable* renderable = m_parts[33]->GetGameObject()->GetRenderables()[0];
		renderable->GetMaterial()->SetParameter("u_color", sm::Vec3(0.9f, 0.9f, 0.9f));
	}
	else if (Input::GetKeyDown(KeyCode_K))
	{
		ShowMechArms(false);
	}
}

void Sphere::CreateMechArms(GameObject* mechArmPrefab)
{
	for (uint32_t i = 0; i < m_parts.size(); i++)
	{
		GameObject* clone = GameObject::Instantiate(mechArmPrefab);

		clone->GetTransform().SetParent(&GetGameObject()->GetTransform());
		clone->GetTransform().SetLocalPosition(m_parts[i]->GetGameObject()->GetTransform().GetLocalPosition() * 0.3f);
		clone->GetTransform().SetForward(m_parts[i]->GetDirection());

		m_mechArms.push_back(dynamic_cast<MechArm*>(clone->GetComponent("MechArm")));
	}
}

void Sphere::SortSphereParts()
{
	std::sort(m_parts.begin(), m_parts.end(), [](SpherePart* a, SpherePart* b)
	{
		return
			a->GetGameObject()->GetTransform().GetPosition().x >
			b->GetGameObject()->GetTransform().GetPosition().x;
	});
}

