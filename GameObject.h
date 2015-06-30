#pragma once

#include "Transform.h"
#include "FuturisEngine/LayerId.h"
#include <Math/Matrix.h>
#include <vector>


class Renderable;
class Light;
class Camera;
class Behaviour;
class Component;

class GameObject
{
public:
	Transform Transform;

	GameObject(const std::string& name);
	virtual ~GameObject();

	const std::vector<Renderable*>& GetRenderables() const;

	bool IsActive() const;

	const std::string& GetName() const;

	void SetLayerId(LayerId layerId);
	LayerId GetLayerId() const;

	void AddRenderable(Renderable* renderable);

	Component* AddComponent(const std::string& componentName);
	Component* GetComponent(const std::string& componentName) const;
	const std::vector<Component*>& GetComponents() const;

protected:
	std::vector<Renderable*> m_renderables;
	std::vector<Component*> m_components;

	bool m_isActive;
	std::string m_name;
	LayerId m_layerId;
};

