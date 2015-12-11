#include "Gunship.h"
#include "../GameObject.h"
#include "../Transform.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../ScenesManager.h"
#include "../Camera.h"
#include "../GraphicsLog.h"

Gunship::Gunship(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_isZoom(false)
{
}

void Gunship::Awake()
{
	m_camera = dynamic_cast<Camera*>(ScenesManager::GetInstance()->FindGameObject("Camera001")->GetComponent("Camera"));
	assert(m_camera != nullptr);
}

void Gunship::Update()
{
	if (Input::GetKeyDown(KeyCode_Space))
		ToggleZoom();
}

void Gunship::FireMachineGun(bool fire)
{

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
	return true;
}
