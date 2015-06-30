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

Component* GameObject::AddComponent(const std::string& componentName)
{
	Component* component = NULL;

	// code below is temporary. All bomponent's factories should be registered
	if (componentName == Light::LightComponentName)
	{
		component = new Light(this);
	}
	else if (componentName == Camera::CameraComponentName)
	{
		component = new Camera(this);
	}
	else
	{
		component = BehavioursManager::GetInstance()->CreateBehaviour(componentName, this);
	}

	if (component != NULL)
		m_components.push_back(component);

	return component;
}

Component* GameObject::GetComponent(const std::string& componentName) const
{
	for (uint32_t i = 0; i < m_components.size(); i++)
	{
		if (m_components[i]->GetComponentName() == componentName)
			return m_components[i];
	}

	return NULL;
}

const std::vector<Component*>& GameObject::GetComponents() const
{
	return m_components;
}

