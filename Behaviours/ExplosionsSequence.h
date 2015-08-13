#pragma once

#include <string>
#include <vector>

class GameObject;
class Sphere;
class Camera;

class ExplosionsSequence
{
public:
	ExplosionsSequence(Sphere* spherePrefab, Camera* mainCamera);

	void Initialize();
	void Prepare();
	void Update();

private:
	Sphere* m_spherePrefab;
	Sphere* m_normalSphere;
	Sphere* m_smallSphere;
	Camera* m_mainCamera;

	void SwapSpheres();
};
