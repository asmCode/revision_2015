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

using namespace FuturisEngine::Graphics;

Sphere::Sphere(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void Sphere::Awake()
{
	DemoUtils::AttachComponentBunch<SpherePart>("SpherePart", "SpherePart", m_parts);
	//DemoUtils::GetAllGameObjectsAsComponent<MechArm>("MechArm", "MechArm", m_mechArms);

	Material* commonMaterial = m_parts[0]->GetGameObject()->GetRenderables()[0]->GetMaterial();

	for (uint32_t i = 0; i < m_parts.size(); i++)
	{
		Material* material = new Material();
		material->SetShader(commonMaterial->GetShader());
		material->SetParameter("u_color", commonMaterial->GetParameterVec3("u_color"));
		material->SetParameter("u_glossiness", commonMaterial->GetParameterFloat("u_glossiness"));
		material->SetParameter("u_specularLevel", commonMaterial->GetParameterFloat("u_specularLevel"));

		m_parts[i]->GetGameObject()->GetRenderables()[0]->SetMaterial(material);

		m_parts[i]->GetPivot()->SetParent(&GetGameObject()->GetTransform());
	}

	CreateMechArms();
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

float angle;

void Sphere::Update()
{
	/*
	angle += Time::DeltaTime * 0.4f;

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
	else if (Input::GetKey(KeyCode_K))
	{
	}
}

void Sphere::CreateMechArms()
{
	GameObject* prefab = ScenesManager::GetInstance()->FindGameObject("MechArm");

	for (uint32_t i = 0; i < m_parts.size(); i++)
	{
		GameObject* clone = GameObject::Instantiate(prefab);

		clone->GetTransform().SetPosition(m_parts[i]->GetGameObject()->GetTransform().GetPosition());
		clone->GetTransform().SetForward(m_parts[i]->GetDirection());

		m_mechArms.push_back(dynamic_cast<MechArm*>(clone->GetComponent("MechArm")));
	}
}
