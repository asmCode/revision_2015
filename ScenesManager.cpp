#include "ScenesManager.h"
#include "Scenes/RevisionTest01.h"
#include "SceneLoader.h"
#include "Scenes/BaseScene.h"
#include "../Environment.h"
#include "../GameObject.h"

ScenesManager* ScenesManager::m_instance;

ScenesManager::ScenesManager() :
	m_isSceneChanged(false),
	m_activeSceneIndex(0)
{
}

ScenesManager* ScenesManager::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new ScenesManager();

	return m_instance;
}

void ScenesManager::Initialize()
{
	BaseScene* baseScene = new BaseScene();
	m_scenes.push_back(baseScene);
	m_isSceneChanged = true;
	m_activeSceneIndex = 0;

	std::string sceneFileName = Environment::GetInstance()->GetBasePath() + "Scenes\\SphereTest.scene";
	SceneLoader sceneLoader;
	sceneLoader.LoadAdditive(sceneFileName);
	sceneLoader.BuildScene(baseScene);

	for (uint32_t i = 0; i < m_scenes.size(); i++)
		m_scenes[i]->Initialize();
}

void ScenesManager::Update(float time)
{
	m_isSceneChanged = false;
}

BaseScene* ScenesManager::GetActiveScene() const
{
	return m_scenes[m_activeSceneIndex];
}

bool ScenesManager::IsSceneChanged() const
{
	return m_isSceneChanged;
}

GameObject* ScenesManager::FindGameObject(const std::string& name) const
{
	if (m_activeSceneIndex < 0 || (uint32_t)m_activeSceneIndex >= m_scenes.size())
	{
		assert(false);
		return NULL;
	}

	std::vector<GameObject*> gameObjects = m_scenes[m_activeSceneIndex]->GetGameObjects();
	for (uint32_t i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetName() == name)
			return gameObjects[i];
	}

	return NULL;
}

