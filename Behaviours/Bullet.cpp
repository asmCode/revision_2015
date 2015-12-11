#include "Bullet.h"
#include "Terrain.h"
#include "ZombieManager.h"
#include "../GameObject.h"
#include "../Transform.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../ScenesManager.h"
#include "../Camera.h"
#include "../GraphicsLog.h"

Bullet::Bullet(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_zombieManager(nullptr),
	m_terrain(nullptr)
{
}

void Bullet::Awake()
{
	m_zombieManager = dynamic_cast<ZombieManager*>(ScenesManager::GetInstance()->FindGameObject("ZombieManager")->GetComponent("ZombieManager"));
	assert(m_zombieManager != nullptr);

	m_terrain = dynamic_cast<Terrain*>(ScenesManager::GetInstance()->FindGameObject("Terrain")->GetComponent("Terrain"));
	assert(m_terrain != nullptr);
}

void Bullet::Update()
{
	if (m_terrain == nullptr)
		Awake();

	sm::Vec3 position = m_gameObject->GetTransform().GetPosition();
	position += m_gameObject->GetTransform().GetForward() * Time::DeltaTime * 50.0f;
	m_gameObject->GetTransform().SetPosition(position);

	float terrainHeight = m_terrain->GetHeight(position);
	if (terrainHeight > position.y)
	{
		m_terrain->NotifyExplosion(position);
		m_zombieManager->NotifyExplosion(position);

		m_gameObject->SetActive(false);
	}
}

void Bullet::Initialize(const sm::Vec3& startPosition, const sm::Vec3& direction)
{
	m_gameObject->GetTransform().SetPosition(startPosition);
	m_gameObject->GetTransform().SetForward(direction);
}
