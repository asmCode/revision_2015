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

void Sphere::Update()
{
	if (Input::GetKey(KeyCode_O))
	{
		Transform& transform = m_parts[Random::GetInt(0, m_parts.size() - 1)]->GetGameObject()->GetTransform();
		transform.SetPosition(transform.GetPosition() + transform.GetPosition().GetNormalized());
	}
}

