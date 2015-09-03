#include "EndlessFlightSequence.h"
#include "../Behaviours/Sphere.h"
#include "../Behaviours/SpherePart.h"
#include "../Behaviours/MainCamera.h"
#include "../Behaviours/SpherePartCommands/PullOut.h"
#include "../Behaviours/SpherePartCommands/PullIn.h"
#include "../Behaviours/SpherePartCommands/SlideOut.h"
#include "../Behaviours/SpherePartCommands/Blink.h"
#include "../Transform.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Camera.h"
#include "../SynchEvent.h"
#include "../../DebugUtils.h"
#include "../../DemoUtils.h"
#include "../FuturisEngine/Time.h"
#include "../Behaviours/SpherePartCommands/Explode.h"
#include "../Behaviours/SpherePartCommands/Reset.h"
#include <UserInput/Input.h>
#include <Utils/Log.h>
#include <Utils/Random.h>

void FadeIn(float speed);
void FadeOut(float speed, bool white);

SpherePart* dd;
int ddIndex;
int ddIndexPrev;
AnimationCurve<sm::Vec3>* oldCurve = nullptr;

bool endFlight;

Sphere* tinySphere;

EndlessFlightSequence::EndlessFlightSequence(GameObject* spherePrefab, GameObject* m_mechArmPrefab, MainCamera* mainCamera) :
m_spherePrefab(spherePrefab),
m_mechArmPrefab(m_mechArmPrefab),
m_mainCamera(mainCamera),
m_speed(0.0f),
m_cameraCurve(nullptr),
m_cameraTime(0.0f)
{

}

float rollAngle;

void EndlessFlightSequence::Initialize()
{
	m_normalSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab)->GetComponent("Sphere"));
	m_normalSphere->Initialize(nullptr);
	m_normalSphere->GetGameObject()->SetActive(false);

	m_smallSphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab)->GetComponent("Sphere"));
	m_smallSphere->Initialize(nullptr);
	m_smallSphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(0.1f, 0.1f, 0.1f));
	m_smallSphere->GetGameObject()->SetActive(false);

	m_tinySphere = dynamic_cast<Sphere*>(GameObject::Instantiate(m_spherePrefab)->GetComponent("Sphere"));
	m_tinySphere->Initialize(nullptr);
	m_tinySphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(0.01f, 0.01f, 0.01f));
	m_tinySphere->GetGameObject()->SetActive(false);

	tinySphere = m_tinySphere;
}


float multi = 3.0f;

void EndlessFlightSequence::Update()
{
	if (Input::GetKeyDown(KeyCode_Space))
	{
		Beat1();
		endFlight = true;
		//m_smallSphere->
	}
		//Repeat();

	if (oldCurve != nullptr)
	{
		//DebugUtils::DrawCurve(*oldCurve, 0.005f, sm::Vec3(0, 1, 0));
	}

	if (m_cameraCurve != nullptr)
	{
		//DebugUtils::DrawCurve(*m_cameraCurve, 0.005f, sm::Vec3(1, 0, 0));

		sm::Vec3 curvePosition = m_cameraCurve->Evaluate(m_cameraTime);

		sm::Vec3 cameraDirection =
			m_mainCamera->GetGameObject()->GetTransform().GetPosition().GetNormalized();

		m_mainCamera->GetGameObject()->GetTransform().SetPosition(curvePosition);
		m_mainCamera->GetLookTransform()->SetForward(cameraDirection);

		rollAngle += Time::DeltaTime * 2.0f;
		
		m_mainCamera->GetLookTransform()->SetRotation(
			sm::Quat::FromAngleAxis(rollAngle, cameraDirection) *
			m_mainCamera->GetLookTransform()->GetRotation());
			

		//m_cameraTime += Time::DeltaTime * 0.5f;
		multi += Time::DeltaTime * 1.1f;
		if (Input::GetKey(KeyCode_T))
			multi *= 0.8f;

		m_cameraTime += Time::DeltaTime * multi;

		if (m_cameraTime >= 0.1f * m_cameraCurve->GetEndTime() && dd != nullptr)
		{
			dd->QueueCommand(new PullOut(0.1f, 0.5f));
			dd->QueueCommand(new SlideOut(0.5f, 0.6f, sm::Vec3(1, 0, 0)));
			dd = nullptr;

			m_normalSphere->GetSphereParts()[ddIndexPrev]->GetGameObject()->SetActive(true);
		}

		/*if (m_cameraTime >= 0.0f * m_cameraCurve->GetEndTime())
		{
			m_normalSphere->GetSphereParts()[ddIndexPrev]->GetGameObject()->SetActive(true);
		}*/

		if (m_cameraTime >= 1.0f * m_cameraCurve->GetEndTime())
		{
			Repeat();
		}
	}
}

void EndlessFlightSequence::Prepare()
{
	srand(3);

	//m_mainCamera->GetGameObject()->GetTransform().SetParent(&m_smallSphere->GetGameObject()->GetTransform());

	Transform* cameraTransform = &ScenesManager::GetInstance()->FindGameObject("InitialEndlessCameraPosition")->GetTransform();
	
	m_mainCamera->GetGameObject()->GetTransform().SetLocalPosition(cameraTransform->GetPosition());
	m_mainCamera->GetGameObject()->GetTransform().SetLocalRotation(cameraTransform->GetRotation());
	m_mainCamera->GetGameObject()->GetTransform().SetLocalScale(cameraTransform->GetLocalScale());
	
	m_mainCamera->GetCamera()->SetFov(2.0f);
	m_mainCamera->EnableSmoothNoise(1.2f, 0.4f);

	m_normalSphere->GetGameObject()->SetActive(true);
	m_smallSphere->GetGameObject()->SetActive(true);
	m_tinySphere->GetGameObject()->SetActive(true);

	/*float distance = m_mainCamera->GetGameObject()->GetTransform().GetLocalPosition().z - 6.0f;
	//m_speed = distance / 1.379f;
	m_speed = 0.0f;
	*/

	Repeat();

	FadeOut(1.0f / 2.0f, true);
}

void EndlessFlightSequence::Clean()
{
	m_normalSphere->GetGameObject()->SetActive(false);
	m_smallSphere->GetGameObject()->SetActive(false);
	m_tinySphere->GetGameObject()->SetActive(false);
}

void EndlessFlightSequence::ExplodeSphere(Sphere* sphere)
{
	const std::vector<SpherePart*>& parts = sphere->GetSphereParts();
	for (uint32_t i = 0; i < parts.size(); i++)
	{
		Explode* command = new Explode();
		parts[i]->SetCommand(command);
	}
}

void EndlessFlightSequence::SwapSpheres()
{
	m_mainCamera->GetGameObject()->GetTransform().SetParent(&m_smallSphere->GetGameObject()->GetTransform());
	m_smallSphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(1, 1, 1));
	m_normalSphere->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(0.1f, 0.1f, 0.1f));
	m_mainCamera->GetGameObject()->GetTransform().SetParent(nullptr);

	Sphere* tmp = m_smallSphere;
	m_smallSphere = m_normalSphere;
	m_normalSphere = tmp;
}

void EndlessFlightSequence::ResetSphere(Sphere* sphere)
{
	const std::vector<SpherePart*>& parts = sphere->GetSphereParts();
	for (uint32_t i = 0; i < parts.size(); i++)
	{
		Reset* command = new Reset();
		parts[i]->SetCommand(command);
	}
}

void EndlessFlightSequence::Repeat()
{
//	m_normalSphere->GetGameObject()->SetActive(true);
//	m_smallSphere->GetGameObject()->SetActive(true);

	if (endFlight)
	{
		SwapSpheres();
		ExplodeSphere(m_smallSphere);
		ExplodeSphere(m_normalSphere);
		m_cameraCurve = nullptr;
		//m_normalSphere->GetGameObject()->SetActive(false);
		m_tinySphere->GetGameObject()->SetActive(false);
	}
	else
	{
		SwapSpheres();

		ResetSphere(m_normalSphere);
		//ResetSphere(m_smallSphere);

		ddIndexPrev = ddIndex;
		m_normalSphere->GetSphereParts()[ddIndex]->GetGameObject()->SetActive(false);

		float distance = m_mainCamera->GetGameObject()->GetTransform().GetLocalPosition().z - 6.0f;
		m_speed = distance / 1.379f;

		if (m_cameraCurve != nullptr)
			m_cameraTime = m_cameraTime - m_cameraCurve->GetEndTime();
		else
		{
			m_cameraTime = 0.0f;
		}

		oldCurve = m_cameraCurve;

		m_cameraCurve = CreateCurve(
			m_mainCamera->GetGameObject()->GetTransform().GetPosition(),
			m_smallSphere,
			m_smallSphere->GetGameObject()->GetTransform().GetPosition());
	}
}

void EndlessFlightSequence::NotifySynchEvent(SynchEvent* synchEvent)
{
	if (synchEvent->GetId() == "end_flight")
	{
		FadeIn(1.0f / 3.0);
		endFlight = true;
	}
}

SpherePart* EndlessFlightSequence::GetRandomPart(Sphere* sphere)
{
	return sphere->GetSphereParts()[Random::GetInt(0, sphere->GetSphereParts().size() - 1)];
}

AnimationCurve<sm::Vec3>* EndlessFlightSequence::CreateCurve(const sm::Vec3& start, Sphere* destinationSphere, const sm::Vec3& pivot)
{
	//const float approachStep = 0.26f;
	const float approachStep = 0.5f;
	const float angleStep = 0.03f;
	const float approachDistanceLimit = 3.0f;
	const float timeStep = 0.1f;

	sm::Vec3 axis = (start.GetNormalized() * Random::GetUniVector() + sm::Vec3(0, Random::GetFloat(-1, 1), Random::GetFloat(-0.3f, 0.3f))).GetNormalized();
	float time = 0.0f;	
	AnimationCurve<sm::Vec3>* curve = new AnimationCurve<sm::Vec3>();

	//curve->AddKeyframe(time - timeStep, start + start.GetNormalized() * approachStep);

	curve->AddKeyframe(time, start);
	curve->AddKeyframe(time += timeStep, start - start.GetNormalized() * approachStep);
	curve->AddKeyframe(time += timeStep, start - start.GetNormalized() * approachStep * 2);
	curve->AddKeyframe(time += timeStep, start - start.GetNormalized() * approachStep * 3);

	float distance = 0.0f;
	sm::Vec3 position = start - start.GetNormalized() * approachStep * 3;
	float angle = 0.0f;
	do
	{
		distance = (pivot - position).GetLength();

		angle += angleStep;
		distance -= approachStep;
		position = position.GetNormalized() * distance;

		sm::Quat rotate = sm::Quat::FromAngleAxis(angle, axis);
		position = rotate.Rotate(position);

		curve->AddKeyframe(time += timeStep, position);
	} while (distance > approachDistanceLimit);

	ddIndex = 0;
	SpherePart* part = destinationSphere->GetClosestPart(position, ddIndex);
	dd = part;
	/*part->QueueCommand(new PullOut(0.3f, 0.5f));
	part->QueueCommand(new SlideOut(0.3f, 0.6f, sm::Vec3(1, 0, 0)));*/
	sm::Vec3 end = part->GetGameObject()->GetTransform().GetPosition();
	m_end = end;


	curve->AddKeyframe(time += timeStep, end + end.GetNormalized() * approachStep * 3);
	curve->AddKeyframe(time += timeStep, end + end.GetNormalized() * approachStep * 2);
	curve->AddKeyframe(time += timeStep, end + end.GetNormalized() * approachStep * 1);
	curve->AddKeyframe(time += timeStep, end);
	curve->SmoothTangents();

	DemoUtils::NormalizeSegments(curve, 0.1f, 1.0f);

	return curve;
}

void EndlessFlightSequence::Beat1()
{
	BlinkSphere(m_smallSphere);
	BlinkSphere(m_normalSphere);
}

void EndlessFlightSequence::BlinkSphere(Sphere* sphere)
{
	const std::vector<SpherePart*>& parts = sphere->GetSphereParts();
	int count = parts.size();

	int* elements = new int[count];

	Random::GetRandomUniqueArray(elements, 0, count - 1);

	for (int i = 0; i < count / 1; i++)
	{
		//parts[elements[i]]->QueueCommand(new PullOut(0.05f, 7.0f));
		//parts[elements[i]]->QueueCommand(new PullIn(0.2f));

		parts[elements[i]]->SetCommandParaller(new Blink(0.2f, sm::Vec3(0.0f, 0.0f, 1)));
	}

	delete[] elements;
}
