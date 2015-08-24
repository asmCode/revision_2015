#include "DemoCamera.h"
#include "../GameObject.h"
#include "../Transform.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"

DemoCamera::DemoCamera(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void DemoCamera::Update()
{
}
