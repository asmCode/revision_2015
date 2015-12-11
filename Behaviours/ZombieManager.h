#pragma once

#include "../Behaviour.h"
#include <Graphics/Point.h>
#include <Math/Quat.h>
#include <string>
#include <vector>

class GameObject;
class Camera;

class ZombieManager : public Behaviour
{
public:
	ZombieManager(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

private:
	GameObject* m_zombiePrefab;

	std::vector<GameObject*> m_spawningPoints;
	GameObject* m_destinationPoint;

	float m_zombiesPerSecond;
	float m_zombieSpawnTimer;

	void SpawnZombie();
};
