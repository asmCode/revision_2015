#include "FppCameraFactory.h"
#include "FppCamera.h"

Behaviour* FppCameraFactory::Create(GameObject* gameObject, const std::string& name)
{
	return new FppCamera(gameObject, name);
}
