#include "BehavioursManager.h"
#include "../Behaviour.h"
#include "../IBehaviourFactory.h"
#include <stddef.h>

BehavioursManager::BehavioursManager()
{
}

BehavioursManager::~BehavioursManager()
{
}

void BehavioursManager::RegisterBehaviour(const std::string& name, IBehaviourFactory* factory)
{

}

Behaviour* BehavioursManager::CreateBehaviour(const std::string& name)
{
	return NULL;
}

void BehavioursManager::UpdateBehaviours()
{

}
