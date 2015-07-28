#include "Sphere.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../Camera.h"
#include "SpherePart.h"
#include "../DemoUtils.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Utils/Random.h>
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

float cipsko = 0.0f;

#include <Utils/Log.h>

void Sphere::Update()
{
	if (Input::GetKey(KeyCode_O))
	{
		//Transform& transform = m_parts[Random::GetInt(0, m_parts.size() - 1)]->GetGameObject()->GetTransform();
		//transform.SetPosition(transform.GetPosition() + transform.GetPosition().GetNormalized());

		//m_parts[33]->Open();

		cipsko += Time::DeltaTime;
	}
	else if (Input::GetKey(KeyCode_K))
	{
		cipsko -= Time::DeltaTime;
	}

	cipsko = MathUtils::Clamp(cipsko, 0.0f, 1.0f);


	sm::Vec3 ray(1, 0.0f, 0);

	sm::Vec3 axis = sm::Vec3(0, 0, 1);
	axis.Normalize();

	sm::Quat q1 = sm::Quat::FromAngleAxis(0.0f, axis);
	sm::Quat q2 = sm::Quat::FromAngleAxis(MathUtils::PI, axis);

	//sm::Quat tq = sm::Quat::Slerp(q1, q2, cipsko);
	QuadOut<sm::Quat> d;
	sm::Quat tq = d.Evaluate(q1, q2, cipsko);
	tq.Normalize();

	ray = tq.Rotate(ray);

	Log::LogT("cipsko = %.2f, tq = (%.2f, %.2f, %.2f, %.2f), ray = (%.2f, %.2f, %.2f)",
		cipsko,
		tq.s, tq.v.x, tq.v.y, tq.v.z,
		ray.x, ray.y, ray.z);

	GraphicsLog::AddSegment(sm::Vec3(0, 0, 0), ray, sm::Vec3(1, 0, 0));
	GraphicsLog::AddSegment(sm::Vec3(0, 0, 0), axis, sm::Vec3(0, 1, 0));
}

