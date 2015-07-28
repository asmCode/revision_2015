#include "Sphere.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../Camera.h"
#include "SpherePart.h"
#include "SpherePartCommands/PullOut.h"
#include "SpherePartCommands/SlideOut.h"
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

void Sphere::Update()
{
	if (Input::GetKeyDown(KeyCode_O))
	{
		//Transform& transform = m_parts[Random::GetInt(0, m_parts.size() - 1)]->GetGameObject()->GetTransform();
		//transform.SetPosition(transform.GetPosition() + transform.GetPosition().GetNormalized());

		PullOut* pullOut = new PullOut(2.0f, 0.5f);
		m_parts[33]->QueueCommand(pullOut);

		SlideOut* slideOut = new SlideOut(2.0f, MathUtils::PI, sm::Vec3(1, 0, 0));
		m_parts[33]->QueueCommand(slideOut);

		//m_parts[33]->Open();
	}
	else if (Input::GetKey(KeyCode_K))
	{
	}
}

