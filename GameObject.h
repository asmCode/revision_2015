#pragma once

#include "FuturisEngine/LayerId.h"
#include <Math/Matrix.h>
#include <vector>


class Transform;
class Renderable;
class Component;

class GameObject
{
public:
	GameObject(const std::string& name);
	virtual ~GameObject();

	const std::vector<Renderable*>& GetRenderables() const;

	void SetActive(bool active);
	bool IsActive() const;

	const std::string& GetName() const;

	void SetLayerId(LayerId layerId);
	LayerId GetLayerId() const;

	void AddRenderable(Renderable* renderable);

	Transform& GetTransform() const;

	GameObject* FindChild(const std::string& name, bool recursive = false) const;

	Component* AddComponent(const std::string& componentName);
	Component* GetComponent(const std::string& componentName) const;
	const std::vector<Component*>& GetComponents() const;

	static GameObject* Instantiate(GameObject* prefab);

protected:
	Transform* m_transform;
	std::vector<Renderable*> m_renderables;
	std::vector<Component*> m_components;

	bool m_isActive;
	std::string m_name;
	LayerId m_layerId;
};

