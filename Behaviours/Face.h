#pragma once

#include "../Behaviour.h"
#include "../Camera.h"
#include <Math/Vec3.h>
#include <string>
#include <vector>

class GameObject;
class Camera;
class Material;
class DepthTexture;

class Face : public Behaviour
{
public:
	Face(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

private:
	Camera* m_camera;
	DepthTexture* m_depthTexture;
	Material* m_depthByZMaterial;
};
