#pragma once

#include "../Behaviour.h"
#include "../CommandHandler.h"
#include <Graphics/Point.h>
#include <string>

class GameObject;
class Transform;
class Camera;
class Noise;
class SmoothNoise;
class Animation;

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
	Animation* GetAnimation() const;

	void HeadBang();
	void Orbit();
	void OrbitFast();
	void OrbitSequence();
	void EnableSmoothNoise(float speed, float angle);

	void PlayBeginningAnim();
	void PlayOpenAnim();

private:
	Transform* m_pivotTransform;
	Transform* m_lookTransform;
	Transform* m_noiseTransform;
	Camera* m_camera;
	Noise* m_noise;
	SmoothNoise* m_smoothNoise;
	Animation* m_animation;
};
