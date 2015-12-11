#include "Gunship.h"
#include "Bullet.h"
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

Gunship::Gunship(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_isZoom(false),
	m_isFiring(false),
	m_fireCooldown(0.0f)
{
}

void Gunship::Awake()
{
	m_camera = dynamic_cast<Camera*>(ScenesManager::GetInstance()->FindGameObject("Camera001")->GetComponent("Camera"));
	assert(m_camera != nullptr);

	m_bulletPrefab = ScenesManager::GetInstance()->FindGameObject("Bullet");
	assert(m_bulletPrefab != nullptr);
	m_bulletPrefab->SetActive(false);
}

void Gunship::Update()
{
	if (Input::GetKeyDown(KeyCode_Space))
		ToggleZoom();

	if (Input::GetKeyDown(KeyCode_LCtrl))
		FireMachineGun(true);
	if (Input::GetKeyUp(KeyCode_LCtrl))
		FireMachineGun(false);

	m_fireCooldown += Time::DeltaTime;

	if (m_isFiring)
	{
		if (m_fireCooldown >= 0.1f)
		{
			m_fireCooldown = 0.0f;
			SpawnBullet();
		}
	}
}

void Gunship::FireMachineGun(bool fire)
{
	m_isFiring = fire;
}

void Gunship::ToggleZoom()
{
	m_isZoom = !m_isZoom;

	if (m_isZoom)
	{
		m_camera->SetFov(0.2f);
	}
	else
	{
		m_camera->SetFov(0.6f);
	}
}

bool Gunship::IsAbleToFire() const
{
	return m_isZoom;
}

void Gunship::SpawnBullet()
{
	GameObject* bulletGo = GameObject::Instantiate(m_bulletPrefab);
	assert(bulletGo != nullptr);

	Bullet* bullet = dynamic_cast<Bullet*>(bulletGo->GetComponent("Bullet"));
	assert(bullet != nullptr);

	sm::Vec3 bulletShift = m_camera->GetGameObject()->GetTransform().GetForward() + sm::Vec3(0, -0.4f, 0);

	sm::Quat bulletRandomRotation =
		sm::Quat::FromAngleAxis(Random::GetFloat(0.0f, 0.01f),
		Random::GetUniVector());

	bullet->Initialize(
		m_camera->GetGameObject()->GetTransform().GetPosition() + bulletShift,
		bulletRandomRotation.Rotate(-m_camera->GetGameObject()->GetTransform().GetForward()));
}
