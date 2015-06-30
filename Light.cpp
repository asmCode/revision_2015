#include "Light.h"

const std::string Light::LightComponentName = "Light";

Light::Light(GameObject* gameObject) :
	Component(LightComponentName, gameObject)
{

}
