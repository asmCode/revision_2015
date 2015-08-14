#pragma once

#include <string>
#include <vector>

class GameObject;
class Sphere;
class Camera;

class ExplosionsSequence
{
public:
	ExplosionsSequence(Sphere* spherePrefab, GameObject* m_mechArmPrefab, Camera* mainCamera);

	void Initialize();
	void Prepare();
	void Update();

	void Repeat();

private:
	Sphere* m_spherePrefab;
	GameObject* m_mechArmPrefab;
	Sphere* m_normalSphere;
	Sphere* m_smallSphere;
	Camera* m_mainCamera;

	float m_speed;

	void SwapSpheres();
	void ResetSphere(Sphere* sphere);
	void ExplodeSphere(Sphere* sphere);
};
