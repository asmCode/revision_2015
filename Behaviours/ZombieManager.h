#pragma once

#include "../Behaviour.h"
#include <Graphics/Point.h>
#include <Math/Quat.h>
#include <string>
#include <vector>

class GameObject;
class Camera;
class Zombie;

class ZombieManager : public Behaviour
{
public:
	ZombieManager(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

	void NotifyExplosion(const sm::Vec3& position);

private:
	GameObject* m_zombiePrefab;

	std::vector<GameObject*> m_spawningPoints;
	GameObject* m_destinationPoint;

	float m_zombiesPerSecond;
	float m_zombieSpawnTimer;

	std::vector<Zombie*> m_zombies;

	void SpawnZombie();
	void DestroyZombies(const sm::Vec3& position, float range);
};
