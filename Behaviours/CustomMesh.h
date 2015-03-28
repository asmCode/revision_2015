#pragma once

#include "../Behaviour.h"
#include <string>

class GameObject;
namespace FuturisEngine { namespace Graphics { class VertexBufferVec3; } }

class CustomMesh : public Behaviour
{
public:
	CustomMesh(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

private:
	FuturisEngine::Graphics::VertexBufferVec3* m_buffer;
};
