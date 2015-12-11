#include "Bullet.h"
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
	Behaviour(gameObject, name)
{
}

void Bullet::Update()
{
	sm::Vec3 position = m_gameObject->GetTransform().GetPosition();
	position += m_gameObject->GetTransform().GetForward() * Time::DeltaTime * 30.0f;
	m_gameObject->GetTransform().SetPosition(position);
}

void Bullet::Initialize(const sm::Vec3& startPosition, const sm::Vec3& direction)
{
	m_gameObject->GetTransform().SetPosition(startPosition);
	m_gameObject->GetTransform().SetForward(direction);
}
