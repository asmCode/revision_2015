#include "BeginningSequence.h"
#include "../GameObject.h"
#include "../Behaviours/Sphere.h"
#include "../Behaviours/SpherePart.h"
#include "../Behaviours/PlaneObject.h"
#include "../Behaviours/Noise.h"
#include "../Behaviours/MainCamera.h"
#include "../Behaviours/SpherePartCommands/PullOut.h"
#include "../Behaviours/SpherePartCommands/PullIn.h"
#include "../Behaviours/TweenCommands/TweenProperty.h"
#include "../Camera.h"
#include "../Transform.h"
#include "../SynchEvent.h"
#include "../FuturisEngine/Time.h"
#include "../PropertyWrapper.h"
#include <Utils/Random.h>
#include <UserInput/Input.h>
#include <Math/Animation/LinearCurve.h>

void FadeIn(float speed);
void FadeOut(float speed, bool white);

BeginningSequence::BeginningSequence(Sphere* sphere, MainCamera* mainCamera):
m_sphere(sphere),
m_mainCamera(mainCamera),
m_pullOutLongBaseIndex(0),
m_groupPlane(nullptr),
m_titlePlane(nullptr)
{
	m_cameraPivot = new GameObject("CameraPivot");

	m_mainCamera->GetGameObject()->GetTransform().SetParent(&m_cameraPivot->GetTransform());
	m_cameraAngle = 0.0f;

	//m_cameraPivot->GetTransform().SetRotation(sm::Quat::FromAngleAxis(1.0f, sm::Vec3(1, 0, 0)));
}

void BeginningSequence::Initialize()
{
	m_groupPlane = PlaneObject::Create("futuris_presents");
	m_groupPlane->GetGameObject()->GetTransform().SetPosition(sm::Vec3(-25, 0, 0));
	m_groupPlane->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(10, 10, 1));
	m_groupPlane->SetSpriteColor(sm::Vec4(1, 1, 1, 0));
	m_titlePlane = PlaneObject::Create("title");
	m_titlePlane->GetGameObject()->GetTransform().SetPosition(sm::Vec3(-11, 0, 0));
	m_titlePlane->GetGameObject()->GetTransform().SetLocalScale(sm::Vec3(5, 5, 1));
	m_titlePlane->GetGameObject()->GetTransform().SetLocalRotation(sm::Quat::FromAngleAxis(3.1415, sm::Vec3(0, 1, 0)));
	m_titlePlane->SetSpriteColor(sm::Vec4(1, 1, 1, 0));

	GameObject* p = new GameObject("TitlePivot");
	m_titlePlane->GetGameObject()->GetTransform().SetParent(&p->GetTransform());
	p->GetTransform().SetRotation(
		sm::Quat::FromAngleAxis(1.3, sm::Vec3(0, 1, 0)) *
		sm::Quat::FromAngleAxis(0.3, sm::Vec3(0, 0, 1)));
}

void BeginningSequence::Prepare()
{
	m_mainCamera->GetGameObject()->GetTransform().SetPosition(sm::Vec3(0, 0, 40));
	m_sphere->GetGameObject()->SetActive(true);

	m_mainCamera->PlayBeginningAnim();

	FadeOut(1.0f / 2.0f, false);
}

void BeginningSequence::Clean()
{
	m_sphere->GetGameObject()->SetActive(false);
}

void BeginningSequence::Update()
{
	ProcessCommands();

	if (Input::GetKeyDown(KeyCode::KeyCode_Space))
	{
		m_sphere->OpenWithMechArms();
		m_sphere->ShowMechArms(false);
	}
}

void BeginningSequence::NotifySynchEvent(SynchEvent* synchEvent)
{
	if (synchEvent->GetId() == "blink1")
	{
		int totalCount = m_sphere->GetSphereParts().size();
		const int subCount = 20;

		int* elements = new int[totalCount];
		Random::GetRandomUniqueArray(elements, 0, totalCount - 1);

		for (int i = 0; i < subCount; i++)
			m_sphere->BlinkSpherePart(elements[i], sm::Vec3(0.9f, 0.9f, 0.9f));

		delete[] elements;
	}
	else if (synchEvent->GetId() == "show_group")
	{
		PropertyWrapperT<PlaneObject, sm::Vec4>* prop = new PropertyWrapperT<PlaneObject, sm::Vec4>(
			m_groupPlane, &PlaneObject::SetSpriteColor, &PlaneObject::GetSpriteColor);

		TweenCommands::TweenProperty<sm::Vec4>* command = new TweenCommands::TweenProperty<sm::Vec4>(
			prop, new LinearCurve<sm::Vec4>(), 2.0f, sm::Vec4(1, 1, 1, 1));

		SetCommandParaller(command);
	}
	else if (synchEvent->GetId() == "hide_group")
	{
		PropertyWrapperT<PlaneObject, sm::Vec4>* prop = new PropertyWrapperT<PlaneObject, sm::Vec4>(
			m_groupPlane, &PlaneObject::SetSpriteColor, &PlaneObject::GetSpriteColor);

		TweenCommands::TweenProperty<sm::Vec4>* command = new TweenCommands::TweenProperty<sm::Vec4>(
			prop, new LinearCurve<sm::Vec4>(), 1.0f, sm::Vec4(1, 1, 1, 0));

		SetCommandParaller(command);
	}
	else if (synchEvent->GetId() == "show_title")
	{
		PropertyWrapperT<PlaneObject, sm::Vec4>* prop = new PropertyWrapperT<PlaneObject, sm::Vec4>(
			m_titlePlane, &PlaneObject::SetSpriteColor, &PlaneObject::GetSpriteColor);

		TweenCommands::TweenProperty<sm::Vec4>* command = new TweenCommands::TweenProperty<sm::Vec4>(
			prop, new LinearCurve<sm::Vec4>(), 2.0f, sm::Vec4(1, 1, 1, 1));

		SetCommandParaller(command);
	}
	else if (synchEvent->GetId() == "hide_title")
	{
		PropertyWrapperT<PlaneObject, sm::Vec4>* prop = new PropertyWrapperT<PlaneObject, sm::Vec4>(
			m_titlePlane, &PlaneObject::SetSpriteColor, &PlaneObject::GetSpriteColor);

		TweenCommands::TweenProperty<sm::Vec4>* command = new TweenCommands::TweenProperty<sm::Vec4>(
			prop, new LinearCurve<sm::Vec4>(), 1.0f, sm::Vec4(1, 1, 1, 0));

		SetCommandParaller(command);
	}
	else if (synchEvent->GetId() == "spin_fast")
	{
		m_sphere->SpinFast();
	}
	else if (synchEvent->GetId() == "spin_fast_end")
	{
		m_mainCamera->EnableSmoothNoise(0.6f, 0.1f);
	}
	else if (synchEvent->GetId() == "beat1")
	{
		const int totalCount = 54;
		const int subCount = 20;

		int elements[totalCount];
		Random::GetRandomUniqueArray(elements, 0, totalCount - 1);

		for (int i = 0; i < subCount; i++)
			m_sphere->RollSpherePart(elements[i]);

		m_mainCamera->OrbitSequence();
	}
	else if (synchEvent->GetId() == "beat1_end")
	{
		m_mainCamera->PlayOpenAnim();
	}
	else if (synchEvent->GetId() == "open_mech1")
	{
		m_sphere->OpenWithMechArms();
	}
	else if (synchEvent->GetId() == "pull_put_long")
	{
		PullOutLong();
	}
}

void BeginningSequence::PullOutLong()
{
	const std::vector<SpherePart*>& parts = m_sphere->GetSphereParts();
	const int groups = 3;

	for (size_t i = 0; i < parts.size(); i++)
	{
		if (i % groups == m_pullOutLongBaseIndex)
			m_sphere->GetSphereParts()[i]->QueueCommand(new PullOut(0.3f, 6.0f));
		else
			m_sphere->GetSphereParts()[i]->QueueCommand(new PullIn(0.3f));
	}

	m_pullOutLongBaseIndex++;
	m_pullOutLongBaseIndex %= groups;
}
