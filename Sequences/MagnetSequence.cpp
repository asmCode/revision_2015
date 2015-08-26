#include "MagnetSequence.h"
#include "../GameObject.h"
#include "../Behaviours/Sphere.h"
#include "../Behaviours/SpherePart.h"
#include "../Behaviours/Magnet.h"
#include "../Behaviours/Noise.h"
#include "../Behaviours/MainCamera.h"
#include "../Behaviours/SpherePartCommands/PullOut.h"
#include "../Behaviours/SpherePartCommands/PullIn.h"
#include "../Behaviours/SpherePartCommands/MagnetCommand.h"
#include "../Behaviours/MainCameraCommands/Animation.h"
#include "../Camera.h"
#include "../Transform.h"
#include "../SynchEvent.h"
#include "../FuturisEngine/Time.h"
#include <Utils/Random.h>
#include <UserInput/Input.h>
#include <Math/MathUtils.h>

MagnetSequence::MagnetSequence(Sphere* sphere, MainCamera* mainCamera) :
m_mainCamera(mainCamera),
m_sphere(sphere)
{
}

void MagnetSequence::Initialize()
{
}

void MagnetSequence::Prepare()
{
	m_mainCamera->GetCamera()->SetFov(90.0f * MathUtils::Deg2Rad);
	m_mainCamera->GetGameObject()->GetTransform().SetPosition(sm::Vec3(0, 0, 40));
	m_mainCamera->ClearCommands();
	m_mainCamera->QueueCommand(new MainCameraCommands::Animation(m_mainCamera, "cam03-01"));

	m_sphere->GetGameObject()->SetActive(true);
	m_sphere->GetNoise()->RotationNoise(0.5f, 0.01f);
	AddMagnet();
	AddMagnet();

	const std::vector<SpherePart*>& parts = m_sphere->GetSphereParts();
	for (size_t i = 0; i < parts.size(); i++)
	{
		parts[i]->SetCommand(new MagnetCommand(m_magnets));
	}
}

void MagnetSequence::Clean()
{
	m_sphere->GetGameObject()->SetActive(false); 
	m_sphere->GetNoise()->RotationNoise(0.0f, 0.0f);
}

void MagnetSequence::Update()
{
	/*
	sm::Vec3 dir = m_magnets[0]->GetGameObject()->GetTransform().GetPosition() - m_mainCamera->GetLookTransform()->GetPosition();
	dir.Normalize();

	m_mainCamera->GetLookTransform()->SetForward(-dir);
	*/
}

void MagnetSequence::NotifySynchEvent(SynchEvent* synchEvent)
{
	if (synchEvent->GetId() == "add_magnet")
	{
	}
}

void MagnetSequence::AddMagnet()
{
	GameObject* magnetGameObject = new GameObject("Magnet");
	Magnet* magnet = dynamic_cast<Magnet*>(magnetGameObject->AddComponent("Magnet"));
	magnet->Initialize(&m_sphere->GetGameObject()->GetTransform());

	m_magnets.push_back(magnet);
}
