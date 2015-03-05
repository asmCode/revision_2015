#include "FuturisEngine.h"
#include "BehavioursManager.h"
#include <stddef.h>

FuturisEngine::FuturisEngine() :
	m_behavioursManager(NULL)
{
}

FuturisEngine::~FuturisEngine()
{
	if (m_behavioursManager != NULL)
		delete m_behavioursManager;
}

bool FuturisEngine::Initialize()
{
	m_behavioursManager = new BehavioursManager();

	return true;
}

BehavioursManager* FuturisEngine::GetBehavioursManager() const
{
	return m_behavioursManager;
}
