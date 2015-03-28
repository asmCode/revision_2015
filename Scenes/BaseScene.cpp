#include "BaseScene.h"
#include "../GameObject.h"
#include "../Environment.h"
#include "../AnimCameraManager.h"
#include "../FuturisEngine/ComponentFlag.h"
#include <Graphics/AnimationData.h>
#include <Graphics/Animation.h>
#include <Graphics/Content/Content.h>
#include <stdint.h>

BaseScene::BaseScene() :
	m_camerasManager(NULL),
	m_camerasAnimation(NULL),
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

	LoadCameras();

	for (uint32_t i = 0; i < m_gameObjects.size(); i++)
	{
		Light* light = m_gameObjects[i]->GetLight();
		if (light != NULL)
			m_lights.push_back(light);

		Camera* camera = m_gameObjects[i]->GetCamera();
		if (camera != NULL)
			m_cameras.push_back(camera);
	}

	return true;
}

float BaseScene::GetStartTime() const
{
	return m_camerasManager->GetCamera(0)->GetStartTime();
}

float BaseScene::GetEndTime() const
{
	return m_camerasManager->GetCamera(m_camerasManager->GetCamerasCount() - 1)->GetLastKeyFrameTime();
}

void BaseScene::NotifySynchEvent(SynchEvent* synchEvent)
{
}

bool BaseScene::Update(float time, float deltaTime)
{
	if (m_camerasAnimation != NULL)
		m_camerasAnimation->Update(time, sm::Matrix::Identity, deltaTime);

	if (m_camerasManager != NULL)
		m_activeCamera = m_camerasManager->GetActiveCamera(time);


	return true;
}

void BaseScene::LoadCameras()
{
	AnimationData* camerasAnimationData = Content::Instance->Get<AnimationData>(m_name);
	if (camerasAnimationData == NULL)
		return;

	m_camerasAnimation = new Animation(camerasAnimationData);

	m_camerasManager = new AnimCameraManager();
	m_camerasManager->Load(Environment::GetInstance()->GetBasePath() + "cameras\\" + m_name + ".cam", m_camerasAnimation);
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
