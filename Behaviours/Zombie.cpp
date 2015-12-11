#include "Zombie.h"
#include "../GameObject.h"
#include "../Transform.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../ScenesManager.h"
#include "../Camera.h"
#include "../GraphicsLog.h"

Zombie::Zombie(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void Zombie::Update()
{
	sm::Vec3 position = m_gameObject->GetTransform().GetPosition();
	position += -m_gameObject->GetTransform().GetForward() * Time::DeltaTime * 5.0f;
	m_gameObject->GetTransform().SetPosition(position);
}

void Zombie::Initialize(const sm::Vec3& startPosition, const sm::Vec3& destination)
{
	m_gameObject->GetTransform().SetPosition(startPosition);
	m_gameObject->GetTransform().SetForward(-(destination - startPosition).GetNormalized());
}
