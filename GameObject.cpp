#include "GameObject.h"
#include "Renderable.h"
#include "Light.h"
#include "Camera.h"
#include "FuturisEngine/Animation/Animation.h"
#include "Transform.h"
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
	m_transform = (Transform*)AddComponent("Transform");

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

Transform& GameObject::GetTransform() const
{
	return *m_transform;
}

GameObject* GameObject::FindChild(const std::string& name, bool recursive) const
{
	const std::vector<Transform*>& children = GetTransform().GetChildren();

	for (uint32_t i = 0; i < children.size(); i++)
	{
		GameObject* child = children[i]->GetGameObject();
		if (child->GetName() == name)
			return child;
		else if (recursive)
		{
			GameObject* childOfChild = child->FindChild(name, recursive);
			if (childOfChild != NULL)
				return childOfChild;
		}
	}

	return NULL;
}

Component* GameObject::AddComponent(const std::string& componentName)
{
	Component* component = NULL;

	// code below is temporary. All component's factories should be registered
	if (componentName == "Transform")
	{
		component = new Transform(this);
	}
	else if (componentName == Light::LightComponentName)
	{
		component = new Light(this);
	}
	else if (componentName == Camera::CameraComponentName)
	{
		component = new Camera(this);
	}
	else if (componentName == "Animation")
	{
		component = new Animation(this);
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

