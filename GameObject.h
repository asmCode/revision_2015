#pragma once

#include <Math/Matrix.h>
#include <vector>
#include "Transform.h"

class Renderable;
class Light;
class Behaviour;

class GameObject
{
public:
	sm::Matrix WorldMatrix;

	Transform Transform;

	GameObject(const std::string& name);
	virtual ~GameObject();

	const std::vector<Renderable*>& GetRenderables() const;

	virtual void Awake();
	virtual void Update(float time, float seconds);

	bool IsActive() const;

	const std::string& GetName() const;

	void AddRenderable(Renderable* renderable);

	void SetLight(Light* light);
	Light* GetLight() const;

	void AddBehaviour(Behaviour* behaviour);
	const std::vector<Behaviour*>& GetBehaviours() const;

protected:
	std::vector<Renderable*> m_renderables;
	std::vector<Behaviour*> m_behaviours;

	Light* m_light;

	bool m_isActive;
	std::string m_name;
};

