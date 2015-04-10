#pragma once

#include "../Behaviour.h"
#include "../Camera.h"
#include <Math/Vec3.h>
#include <string>
#include <vector>

class GameObject;
class Texture;
class DepthTexture;
class Camera;

class RttTest :	public Behaviour
{
public:
	RttTest(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

private:
	Texture* m_renderTexture;
	DepthTexture* m_depthTexture;
	Camera* m_camera;
};
