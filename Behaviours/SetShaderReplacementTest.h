#pragma once

#include "../Behaviour.h"
#include "../Camera.h"
#include <Math/Vec3.h>
#include <string>
#include <vector>

class GameObject;
class Camera;
class Material;

class SetShaderReplacementTest : public Behaviour
{
public:
	SetShaderReplacementTest(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

private:
	Camera* m_camera;
	
	Material* m_replacementMaterial1;
	Material* m_replacementMaterial2;
};
