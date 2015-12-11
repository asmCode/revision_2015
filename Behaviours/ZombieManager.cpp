#include "ZombieManager.h"
#include "Zombie.h"
#include "../GameObject.h"
#include "../Transform.h"
#include <UserInput/Input.h>
#include <Utils/Random.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../ScenesManager.h"
#include "../Camera.h"
#include "../GraphicsLog.h"
#include "../DemoUtils.h"
#include "../Scenes/BaseScene.h"

ZombieManager::ZombieManager(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_zombiePrefab(nullptr),
	m_destinationPoint(nullptr),
	m_zombieSpawnTimer(0.0f)
{
	RegisterParameter("zombie_per_second", &m_zombiesPerSecond);
}

void ZombieManager::Awake()
{
	m_zombiePrefab = ScenesManager::GetInstance()->FindGameObject("Zombie");
	assert(m_zombiePrefab != nullptr);
	m_zombiePrefab->SetActive(false);

	DemoUtils::GetAllObjects("Source", m_spawningPoints);

	m_destinationPoint = ScenesManager::GetInstance()->FindGameObject("Target");
}

void ZombieManager::Update()
{
	m_zombieSpawnTimer += Time::DeltaTime * m_zombiesPerSecond;
	if (m_zombieSpawnTimer >= 1.0f)
	{
		for (int i = 0; i < (int)m_zombiesPerSecond; i++)
			SpawnZombie();

		m_zombieSpawnTimer -= (float)((int)m_zombiesPerSecond);
	}
}

void ZombieManager::SpawnZombie()
{
	GameObject* zombieGo = GameObject::Instantiate(m_zombiePrefab);
	assert(zombieGo != nullptr);

	Zombie* zombie = dynamic_cast<Zombie*>(zombieGo->GetComponent("Zombie"));
	assert(zombie != nullptr);

	sm::Vec3 position = m_spawningPoints[Random::GetInt(0, m_spawningPoints.size() - 1)]->GetTransform().GetPosition();

	zombie->Initialize(position, m_destinationPoint->GetTransform().GetPosition());
}
