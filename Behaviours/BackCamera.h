#pragma once

#include "../Behaviour.h"
#include <string>

class GameObject;
class Transform;
class Camera;
class MainCamera;
class Noise;
class SmoothNoise;
class Animation;
class Sphere;
class Texture;
class TextureImage;

class BackCamera : public Behaviour
{
public:
	BackCamera(GameObject* gameObject, const std::string& name);

	void Initialize(MainCamera* mainCamera, GameObject* spherePrefab);

	void Awake();
	void Update();

private:
	GameObject* m_spherePrefab;
	MainCamera* m_mainCamera;
	Camera* m_camera;
	Texture* m_renderTarget;
	TextureImage* m_textureImage;

	Sphere* m_sphere1;
	Sphere* m_sphere2;

	void PrepareBg();
	void PrepareSphere(Sphere* sphere, float scale, float dist, float angle);
};
