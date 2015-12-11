#pragma once

#include "../Behaviour.h"
#include <Graphics/Point.h>
#include <Math/Quat.h>
#include <string>

class GameObject;
class Camera;
class ZombieManager;
class Terrain;

class Bullet : public Behaviour
{
public:
	Bullet(GameObject* gameObject, const std::string& name);

	void Update();
	void Awake();
	void Initialize(const sm::Vec3& startPosition, const sm::Vec3& direction);

private:
	ZombieManager* m_zombieManager;
	Terrain* m_terrain;
};
