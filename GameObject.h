#pragma once

#include <Math/Matrix.h>
#include <vector>
#include "Transform.h"

class Renderable;
class Light;
class Camera;
class Behaviour;

class GameObject
{
public:
	Transform Transform;

	GameObject(const std::string& name);
	virtual ~GameObject();

	const std::vector<Renderable*>& GetRenderables() const;

	bool IsActive() const;

	const std::string& GetName() const;

	void AddRenderable(Renderable* renderable);

	void SetLight(Light* light);
	Light* GetLight() const;

	void SetCamera(Camera* camera);
	Camera* GetCamera() const;

	void AddBehaviour(Behaviour* behaviour);
	Behaviour* AddBehaviour(const std::string& componentName);
	const std::vector<Behaviour*>& GetBehaviours() const;

protected:
	std::vector<Renderable*> m_renderables;
	std::vector<Behaviour*> m_behaviours;

	Light* m_light;
	Camera* m_camera;

	bool m_isActive;
	std::string m_name;
};

