#pragma once

#include "../Behaviour.h"
#include <Math/Vec4.h>
#include <string>

class GameObject;

class TextureImage : public Behaviour
{
public:
	TextureImage(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

private:
	std::string m_textureName;
	sm::Vec4 m_bounds;
	sm::Vec4 m_coords;
};

