#include "GameObject.h"
#include "Renderable.h"
#include "Light.h"
#include "Camera.h"
#include "../FuturisEngine/BehavioursManager.h"
#include "../Behaviour.h"
#include "../FuturisEngine/ComponentFlag.h"
#include "../ScenesManager.h"
#include "../Scenes/BaseScene.h"
#include <stddef.h>

GameObject::GameObject(const std::string& name) :
	m_name(name),
	m_isActive(true),
	m_light(NULL),
	m_camera(NULL),
	m_layerId(LayerId_0)
{
	BaseScene* scene = ScenesManager::GetInstance()->GetActiveScene();
	scene->NotifyNewGameObject(this);
}

GameObject::~GameObject()
{
}

const std::vector<Renderable*>& GameObject::GetRenderables() const
{
	return m_renderables;
}

bool GameObject::IsActive() const
{
	return m_isActive;
}

const std::string& GameObject::GetName() const
{
	return m_name;
}

void GameObject::SetLayerId(LayerId layerId)
{
	m_layerId = layerId;
}

LayerId GameObject::GetLayerId() const
{
	return m_layerId;
}

void GameObject::AddRenderable(Renderable* renderable)
{
	m_renderables.push_back(renderable);

	BaseScene* scene = ScenesManager::GetInstance()->GetActiveScene();
	scene->NotifyNewComponent(this, ComponentFlag::Mesh);
}

void GameObject::SetLight(Light* light)
{
	m_light = light;
}

Light* GameObject::GetLight() const
{
	return m_light;
}

void GameObject::SetCamera(Camera* camera)
{
	m_camera = camera;
}

Camera* GameObject::GetCamera() const
{
	return m_camera;
}

void GameObject::AddBehaviour(Behaviour* behaviour)
{
	m_behaviours.push_back(behaviour);
}

Behaviour* GameObject::AddBehaviour(const std::string& componentName)
{
	Behaviour* behaviour = BehavioursManager::GetInstance()->CreateBehaviour(componentName, this);
	if (behaviour != NULL)
		m_behaviours.push_back(behaviour);

	return behaviour;
}

Behaviour* GameObject::GetBehaviour(const std::string& componentName) const
{
	for (uint32_t i = 0; i < m_behaviours.size(); i++)
	{
		if (m_behaviours[i]->GetName() == componentName)
			return m_behaviours[i];
	}

	return NULL;
}

const std::vector<Behaviour*>& GameObject::GetBehaviours() const
{
	return m_behaviours;
}

