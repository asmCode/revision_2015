#include "Zombie.h"
#include "Terrain.h"
#include "../GameObject.h"
#include "../Transform.h"
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../ScenesManager.h"
#include "../Camera.h"
#include "../GraphicsLog.h"

#include "../../FuturisEngine/Animation/AnimationClip.h"
#include <Graphics/Content/Content.h>

Zombie::Zombie(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void Zombie::Update()
{
	sm::Vec3 position = m_gameObject->GetTransform().GetPosition();
	position += -m_gameObject->GetTransform().GetForward() * Time::DeltaTime * 2.0f;
	position.y = m_terrain->GetHeight(position);
	m_gameObject->GetTransform().SetPosition(position);

	animation->Update();
}

void Zombie::Initialize(Terrain* terrain, const sm::Vec3& startPosition, const sm::Vec3& destination)
{
	m_terrain = terrain;
	m_gameObject->GetTransform().SetPosition(startPosition);
	m_gameObject->GetTransform().SetForward(-(destination - startPosition).GetNormalized());

	AnimationClip* clip = Content::Instance->Get<AnimationClip>("Zombie");
	animation = dynamic_cast<::Animation*>(m_gameObject->GetComponent("Animation"));
	animation->SetAnimationClip(clip);
	animation->Play();
}
