#include "GameObject.h"
#include "Renderable.h"
#include "Light.h"
#include "Camera.h"
#include "../FuturisEngine/BehavioursManager.h"
#include <stddef.h>

GameObject::GameObject(const std::string& name) :
	m_name(name),
	m_isActive(true),
	m_light(NULL),
	m_camera(NULL)
{
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

void GameObject::AddRenderable(Renderable* renderable)
{
	m_renderables.push_back(renderable);
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

const std::vector<Behaviour*>& GameObject::GetBehaviours() const
{
	return m_behaviours;
}
