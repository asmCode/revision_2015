#include "BehavioursManager.h"
#include "../Behaviour.h"
#include "../IBehaviourFactory.h"
#include <Utils/MapUtils.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

BehavioursManager::BehavioursManager()
{
}

BehavioursManager::~BehavioursManager()
{
	for (uint32_t i = 0; i < m_behaviours.size(); i++)
		delete m_behaviours[i];
}

void BehavioursManager::RegisterBehaviour(const std::string& name, IBehaviourFactory* factory)
{
	if (MapUtils::HasKey(m_behavioursFactories, name))
	{
		assert(false);
		return;
	}

	m_behavioursFactories[name] = factory;
}

Behaviour* BehavioursManager::CreateBehaviour(const std::string& name, GameObject *gameObject)
{
	IBehaviourFactory* behaviourFactory = MapUtils::Find(m_behavioursFactories, name);
	if (behaviourFactory == NULL)
		return NULL;

	Behaviour* behaviour = behaviourFactory->Create(gameObject, name);

	m_behaviours.push_back(behaviour);

	return behaviour;
}

void BehavioursManager::UpdateBehaviours()
{
	for (uint32_t i = 0; i < m_behaviours.size(); i++)
		m_behaviours[i]->Update();
}
