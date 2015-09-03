#include "ExplosionsSequence.h"
#include "../Behaviours/Sphere.h"
#include "../Behaviours/PlaneObject.h"
#include "../Behaviours/SpherePart.h"
#include "../Behaviours/SpherePartCommands/PullOut.h"
#include "../Behaviours/SpherePartCommands/PullIn.h"
#include "../Behaviours/SpherePartCommands/SlideOut.h"
#include "../Behaviours/TweenCommands/TweenProperty.h"
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
#include <Math/Animation/QuadOut.h>
#include <Math/Animation/QuadIn.h>
#include <Math/Animation/QuadInOut.h>

bool m_isBreaking;
float m_speedBase;
float m_breakTime;

extern Sphere* tinySphere;

ExplosionsSequence::ExplosionsSequence(GameObject* spherePrefab, GameObject* m_mechArmPrefab, MainCamera* mainCamera) :
m_spherePrefab(spherePrefab),
m_mechArmPrefab(m_mechArmPrefab),
m_mainCamera(mainCamera),
m_speed(0.0f),
m_greetzIndex(0)
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

	for (int i = 0; i < 16; i++)
	{
		char name[12];
		sprintf(name, "greetz%d", i);
		PlaneObject* plane = PlaneObject::Create(name);
		//plane->GetGameObject()->GetTransform().SetPosition(sm::Vec3(1.2, 0, 0));
		plane->GetGameObject()->GetTransform().SetPosition(sm::Vec3(-1.0f, -0.0f, 1.2f));
		plane->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(2, 2, 1));
		m_greetz.push_back(plane);

		GameObject* p = new GameObject("GreetzParent");
		plane->GetGameObject()->GetTransform().SetParent(&p->GetTransform());
		//p->GetTransform().SetLocalRotation(
//			sm::Quat::FromAngleAxis((float)(i % 3 - 1) * 0.3f, sm::Vec3(0, 0, 1)));

		plane->GetGameObject()->SetActive(false);
	}
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
int explodeIndex;

void ExplosionsSequence::Prepare()
{
	m_mainCamera->GetGameObject()->GetTransform().SetParent(&m_smallSphere->GetGameObject()->GetTransform());
	m_mainCamera->ClearCommands();
	m_mainCamera->GetCamera()->SetFov(90.0f * MathUtils::Deg2Rad);
	m_mainCamera->EnableSmoothNoise(1.0f, 0.3f);
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

	m_greetz[explodeIndex * 3 + 0]->GetGameObject()->SetActive(true);
	//m_greetz[explodeIndex * 3 + 1]->GetGameObject()->SetActive(true);
	//m_greetz[explodeIndex * 3 + 2]->GetGameObject()->SetActive(true);
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

	for (size_t i = 0; i < m_greetz.size(); i++)
	{
		m_greetz[i]->GetGameObject()->SetActive(false);
	}

	explodeIndex++;

	if (explodeIndex < m_greetz.size())
		m_greetz[explodeIndex * 1 + 0]->GetGameObject()->SetActive(true);
	//m_greetz[explodeIndex * 3 + 0]->GetGameObject()->SetActive(true);
	//m_greetz[explodeIndex * 3 + 1]->GetGameObject()->SetActive(true);
	//m_greetz[explodeIndex * 3 + 2]->GetGameObject()->SetActive(true);
}

void ExplosionsSequence::NotifySynchEvent(SynchEvent* synchEvent)
{
	if (synchEvent->GetId() == "explode")
	{
		Repeat();
	}
	else if (synchEvent->GetId() == "break")
	{
		//m_mainCamera->GetLookTransform()->SetLocalRotation(sm::Quat(1, 0, 0, 0));

		PropertyWrapperT<Transform, sm::Quat>* prop = new PropertyWrapperT<Transform, sm::Quat>(
			m_mainCamera->GetNoiseTransform(), &Transform::SetLocalRotation, &Transform::GetLocalRotation);

		TweenCommands::TweenProperty<sm::Quat>* command = new TweenCommands::TweenProperty<sm::Quat>(
			prop, new QuadInOut<sm::Quat>(), 1.0f, sm::Quat(1, 0, 0, 0));

		m_mainCamera->SetCommandParaller(command);

		////////////////
		prop = new PropertyWrapperT<Transform, sm::Quat>(
			&m_smallSphere->GetGameObject()->GetTransform(), &Transform::SetLocalRotation, &Transform::GetLocalRotation);

		command = new TweenCommands::TweenProperty<sm::Quat>(
			prop, new QuadInOut<sm::Quat>(), 1.0f,
			sm::Quat::FromAngleAxis(0.5f, sm::Vec3(0, 1, 0)) *
			sm::Quat::FromAngleAxis(-0.0f, sm::Vec3(1, 0, 0)));

		m_smallSphere->SetCommandParaller(command);
		////////////////

		//m_mainCamera->GetNoiseTransform()->SetLocalRotation(sm::Quat(1, 0, 0, 0));

		tinySphere->GetGameObject()->SetActive(true);
		m_isBreaking = true;
		m_speedBase = m_speed;
		m_mainCamera->EnableSmoothNoise(0.0f, 0.0f);
	}
	else if (synchEvent->GetId() == "open_gate")
	{
		SpherePart* dd = m_smallSphere->GetClosestPart(m_mainCamera->GetRootTransform()->GetPosition());
		dd->QueueCommand(new PullOut(0.4f, 1.5f));
		dd->QueueCommand(new SlideOut(0.8f, 0.6f, sm::Vec3(1, 0, 0)));
	}
}
