#include "Sphere.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../Camera.h"
#include "SpherePart.h"
#include "SpherePartCommands/PullOut.h"
#include "SpherePartCommands/PullIn.h"
#include "SpherePartCommands/SlideOut.h"
#include "SpherePartCommands/SlideIn.h"
#include "SpherePartCommands/RollOut.h"
#include "SpherePartCommands/RollIn.h"
#include "../DemoUtils.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Utils/Random.h>
#include <Utils/Log.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"

Sphere::Sphere(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void Sphere::Awake()
{
	DemoUtils::AttachComponentBunch<SpherePart>("SpherePart", "SpherePart", m_parts);
}

void Sphere::RollSpherePart(int index)
{
	//int index = Random::GetInt(0, m_parts.size() - 1);
	//int index = 33;

	PullOut* pullOut = new PullOut(0.34f, 1.2f);
	m_parts[index]->QueueCommand(pullOut);

	/*
	SlideOut* slideOut = new SlideOut(0.5f, MathUtils::PI / 6.0f, sm::Vec3(1, 0, 0));
	m_parts[index]->QueueCommand(slideOut);

	SlideIn* slideIn = new SlideIn(0.5f);
	m_parts[index]->QueueCommand(slideIn);
	*/

	RollOut* rollOut = new RollOut(0.34f, MathUtils::PI2 - 0.01f);
	m_parts[index]->QueueCommand(rollOut);

	RollIn* rollIn = new RollIn(0.34f);
	m_parts[index]->QueueCommand(rollIn);

	PullIn* pullIn = new PullIn(0.34f);
	m_parts[index]->QueueCommand(pullIn);
}

void Sphere::Update()
{
	if (Input::GetKeyDown(KeyCode_O))
	{
		//Transform& transform = m_parts[Random::GetInt(0, m_parts.size() - 1)]->GetGameObject()->GetTransform();
		//transform.SetPosition(transform.GetPosition() + transform.GetPosition().GetNormalized());

		int index = Random::GetInt(0, m_parts.size() - 1);
		//int index = 33;

		PullOut* pullOut = new PullOut(0.3f, 0.5f);
		m_parts[index]->QueueCommand(pullOut);

		/*
		SlideOut* slideOut = new SlideOut(0.5f, MathUtils::PI / 6.0f, sm::Vec3(1, 0, 0));
		m_parts[index]->QueueCommand(slideOut);

		SlideIn* slideIn = new SlideIn(0.5f);
		m_parts[index]->QueueCommand(slideIn);
		*/

		RollOut* rollOut = new RollOut(0.5f, MathUtils::PI);
		m_parts[index]->QueueCommand(rollOut);

		RollIn* rollIn = new RollIn(0.5f);
		m_parts[index]->QueueCommand(rollIn);

		PullIn* pullIn = new PullIn(0.5f);
		m_parts[index]->QueueCommand(pullIn);

		//m_parts[33]->Open();
	}
	else if (Input::GetKey(KeyCode_K))
	{
	}
}

