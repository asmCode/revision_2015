#include "BaseScene.h"
#include "../GameObject.h"
#include "../Environment.h"
#include "../Light.h"
#include "../Camera.h"
#include "../FuturisEngine/ComponentFlag.h"
#include <Graphics/Content/Content.h>
#include <stdint.h>

BaseScene::BaseScene() :
	m_activeCamera(NULL),
	m_hasSceneChanged(false)
{
};

const std::vector<GameObject*>& BaseScene::GetGameObjects() const
{
	return m_gameObjects;
}

const std::vector<Renderable*>& BaseScene::GetRenderables() const
{
	return m_renderables;
}

const std::vector<Light*>& BaseScene::GetLights() const
{
	return m_lights;
}

const std::vector<Camera*>& BaseScene::GetCameras() const
{
	return m_cameras;
}

ICamera* BaseScene::GetCamera() const
{
	return m_activeCamera;
}

bool BaseScene::Initialize()
{
	InitializeSubScene();

	for (uint32_t i = 0; i < m_gameObjects.size(); i++)
	{
		Light* light = (Light*)m_gameObjects[i]->GetComponent(Light::LightComponentName);
		if (light != NULL)
			m_lights.push_back(light);

		Camera* camera = (Camera*)m_gameObjects[i]->GetComponent(Camera::CameraComponentName);
		if (camera != NULL)
			m_cameras.push_back(camera);
	}

	return true;
}

void BaseScene::NotifySynchEvent(SynchEvent* synchEvent)
{
}

bool BaseScene::Update(float time, float deltaTime)
{
	return true;
}

GameObject* BaseScene::FindGameObject(const std::string& name)
{
	for (uint32_t i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_gameObjects[i]->GetName() == name)
			return m_gameObjects[i];
	}

	return NULL;
}

void BaseScene::NotifyNewGameObject(GameObject* gameObject)
{
	m_gameObjects.push_back(gameObject);

	m_hasSceneChanged = true;
}

void BaseScene::NotifyNewComponent(GameObject* gameObject, int componentFlag)
{
	if (componentFlag & ComponentFlag::Mesh)
		m_renderables.insert(m_renderables.end(), gameObject->GetRenderables().begin(), gameObject->GetRenderables().end());

	m_hasSceneChanged = true;
}

bool BaseScene::HasSceneChanged() const
{
	return m_hasSceneChanged;
}

void BaseScene::ClearSceneChangedFlag()
{
	m_hasSceneChanged = false;
}
