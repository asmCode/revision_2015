#include "OutroSequence.h"
#include "../GameObject.h"
#include "../Behaviours/Sphere.h"
#include "../Behaviours/SpherePart.h"
#include "../Behaviours/PlaneObject.h"
#include "../Behaviours/Noise.h"
#include "../Behaviours/SmoothNoise.h"
#include "../Behaviours/MainCamera.h"
#include "../Behaviours/SpherePartCommands/PullOut.h"
#include "../Behaviours/SpherePartCommands/PullIn.h"
#include "../Behaviours/TweenCommands/TweenProperty.h"
#include "../Camera.h"
#include "../Transform.h"
#include "../SynchEvent.h"
#include "../FuturisEngine/Time.h"
#include "../../ScenesManager.h"
#include "../FuturisEngine/Animation/Animation.h"
#include "../PropertyWrapper.h"
#include <Utils/Random.h>
#include <UserInput/Input.h>
#include <Math/Animation/LinearCurve.h>
#include <Math/Animation/Custom/BlinkCurve.h>

extern bool showOutro;
void FadeIn(float speed);
void FadeOut(float speed);

OutroSequence::OutroSequence(Sphere* sphere, MainCamera* mainCamera):
m_sphere(sphere),
m_mainCamera(mainCamera)
{
	m_smoothNoise = dynamic_cast<SmoothNoise*>(sphere->GetGameObject()->GetComponent("SmoothNoise"));
}

void OutroSequence::Initialize()
{
}

void OutroSequence::Prepare()
{
	m_sphere->Reset();
	m_sphere->GetGameObject()->SetActive(true);

	m_mainCamera->ClearCommands();
	m_mainCamera->GetCamera()->SetFov(60.0f * MathUtils::Deg2Rad);
	m_mainCamera->EnableSmoothNoise(false, false);

	Transform* cameraTransform = &ScenesManager::GetInstance()->FindGameObject("InitialOutroCameraPosition")->GetTransform();

	m_mainCamera->GetGameObject()->GetTransform().SetLocalPosition(cameraTransform->GetPosition());
	m_mainCamera->GetGameObject()->GetTransform().SetLocalRotation(cameraTransform->GetRotation());
	m_mainCamera->GetGameObject()->GetTransform().SetLocalScale(cameraTransform->GetLocalScale());

	m_smoothNoise->RotationNoise(0.1f, MathUtils::PI);
	PullOutLong();

	FadeOut(1.0f / 3.0f);
	showOutro = true;
}

void OutroSequence::Clean()
{
	m_sphere->GetGameObject()->SetActive(false);
}

void OutroSequence::Update()
{
}

void OutroSequence::NotifySynchEvent(SynchEvent* synchEvent)
{
}

void OutroSequence::PullOutLong()
{
	const std::vector<SpherePart*>& parts = m_sphere->GetSphereParts();
	const int groups = 3;

	for (size_t i = 0; i < parts.size(); i++)
	{
		if (i % groups == 0)
			m_sphere->GetSphereParts()[i]->QueueCommand(new PullOut(0.3f, 6.0f));
		else
			m_sphere->GetSphereParts()[i]->QueueCommand(new PullIn(0.3f));
	}
}
