#include "BehavioursManager.h"
#include "../Behaviour.h"
#include "../GameObject.h"
#include "../IBehaviourFactory.h"
#include <Utils/MapUtils.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

BehavioursManager* BehavioursManager::m_instance;

BehavioursManager* BehavioursManager::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new BehavioursManager();

	return m_instance;
}

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
	m_behavioursToAwake.push_back(behaviour);

	return behaviour;
}

void BehavioursManager::UpdateBehaviours()
{
	for (uint32_t i = 0; i < m_behaviours.size(); i++)
	{
		if (!m_behaviours[i]->IsDestroyed() && m_behaviours[i]->GetGameObject()->IsActive())
			m_behaviours[i]->Update();
	}
}

void BehavioursManager::AwakeBehaviours()
{
	while (m_behavioursToAwake.size() > 0)
	{
		// Behaviours trzeba skopiowac do innego wektora, bo podczas wywolywania Awake() nowe Behavioury
		// moga zostac stworzone (a tym samym dodane do listy m_behavioursToAwake
		BehavioursVector toAwake(m_behavioursToAwake);

		m_behavioursToAwake.clear();

		for (uint32_t i = 0; i < toAwake.size(); i++)
			toAwake[i]->Awake();
	}
}
