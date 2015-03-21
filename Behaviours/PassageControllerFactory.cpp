#include "PassageControllerFactory.h"
#include "PassageController.h"

Behaviour* PassageControllerFactory::Create(GameObject* gameObject, const std::string& name)
{
	return new PassageController(gameObject, name);
}
