#include "SpherePart.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../Camera.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"

SpherePart::SpherePart(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void SpherePart::Awake()
{
}

void SpherePart::Update()
{
}

