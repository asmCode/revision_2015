#include "JumpFactory.h"
#include "Jump.h"

Behaviour* JumpFactory::Create(GameObject* gameObject, const std::string& name)
{
	return new Jump(gameObject, name);
}
