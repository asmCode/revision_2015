#pragma once

#include "Transform.h"
#include "FuturisEngine/LayerId.h"
#include <Math/Matrix.h>
#include <vector>


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

	void SetLayerId(LayerId layerId);
	LayerId GetLayerId() const;

	void AddRenderable(Renderable* renderable);

	void SetLight(Light* light);
	Light* GetLight() const;

	void SetCamera(Camera* camera);
	Camera* GetCamera() const;

	void AddBehaviour(Behaviour* behaviour);
	Behaviour* AddBehaviour(const std::string& componentName);
	Behaviour* GetBehaviour(const std::string& componentName) const;
	const std::vector<Behaviour*>& GetBehaviours() const;

protected:
	std::vector<Renderable*> m_renderables;
	std::vector<Behaviour*> m_behaviours;

	bool m_isActive;
	std::string m_name;
	LayerId m_layerId;

	Light* m_light;
	Camera* m_camera;
};

