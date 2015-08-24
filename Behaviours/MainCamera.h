#pragma once

#include "../Behaviour.h"
#include "../CommandHandler.h"
#include <Graphics/Point.h>
#include <string>

class GameObject;
class Transform;
class Camera;
class Noise;

class MainCamera : public Behaviour, public CommandHandler<MainCamera*>
{
public:
	MainCamera(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

	Transform* GetPivotTransform();
	Transform* GetRootTransform();
	Transform* GetLookTransform();
	Transform* GetNoiseTransform();
	Camera* GetCamera();
	Noise* GetNoise();

	void HeadBang();
	void Orbit();

private:
	Transform* m_pivotTransform;
	Transform* m_lookTransform;
	Transform* m_noiseTransform;
	Camera* m_camera;
	Noise* m_noise;
};
