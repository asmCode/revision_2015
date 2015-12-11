#pragma once

#include <vector>

class GameObject;
class Light;
class Camera;
class Renderable;
class ICamera;
class SynchEvent;

class BaseScene
{
	friend class SceneLoader;

public:
	BaseScene();
	virtual ~BaseScene() {}

	bool Initialize();

	virtual bool Update(float time, float deltaTime);

	virtual void Enter() {};
	virtual void Leave() {};

	const std::vector<GameObject*>& GetGameObjects() const;
	const std::vector<Renderable*>& GetRenderables() const;
	const std::vector<Light*>& GetLights() const;
	const std::vector<Camera*>& GetCameras() const;

	bool HasSceneChanged() const;
	void ClearSceneChangedFlag();

	void NotifyNewGameObject(GameObject* gameObject);
	void NotifyDestroyedGameObject(GameObject* gameObject);
	void NotifyNewComponent(GameObject* gameObject, int componentFlag);

	virtual ICamera* GetCamera() const;

	virtual void NotifySynchEvent(SynchEvent* synchEvent);

protected:
	std::string m_name;

	std::vector<GameObject*> m_gameObjects;
	std::vector<Renderable*> m_renderables;
	std::vector<Light*> m_lights;
	std::vector<Camera*> m_cameras;

	ICamera* m_activeCamera;

	bool m_hasSceneChanged;

	virtual void InitializeSubScene() {};

	GameObject* FindGameObject(const std::string& name);

	template <typename T>
	void GetGameObjectsOfType(std::vector<T>& gameObjects)
	{
		for (uint32_t i = 0; i < m_gameObjects.size(); i++)
		{
			T gameObject = dynamic_cast<T>(m_gameObjects[i]);
			if (gameObject != NULL)
				gameObjects.push_back(gameObject);
		}
	}
};

