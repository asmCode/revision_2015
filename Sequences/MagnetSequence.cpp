#include "MagnetSequence.h"
#include "../GameObject.h"
#include "../Behaviours/Sphere.h"
#include "../Behaviours/SpherePart.h"
#include "../Behaviours/Magnet.h"
#include "../Behaviours/SpherePartCommands/PullOut.h"
#include "../Behaviours/SpherePartCommands/PullIn.h"
#include "../Camera.h"
#include "../Transform.h"
#include "../SynchEvent.h"
#include "../FuturisEngine/Time.h"
#include <Utils/Random.h>
#include <UserInput/Input.h>

MagnetSequence::MagnetSequence(Sphere* sphere, Camera* mainCamera):
m_mainCamera(mainCamera),
m_sphere(sphere)
{
}

void MagnetSequence::Initialize()
{
}

void MagnetSequence::Prepare()
{
	m_sphere->GetGameObject()->SetActive(true);
	AddMagnet();
}

void MagnetSequence::Clean()
{
	m_sphere->GetGameObject()->SetActive(false);
}

void MagnetSequence::Update()
{
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
}
