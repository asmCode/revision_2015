#pragma once

#include "../Behaviour.h"
#include "../FuturisEngine/Graphics/VertexBufferVec3.h"
#include "../FuturisEngine/Graphics/IndexBuffer.h"
#include <string>

class GameObject;

class CustomMesh : public Behaviour
{
public:
	CustomMesh(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

private:
	FuturisEngine::Graphics::VertexBufferVec3* m_buffer;
	FuturisEngine::Graphics::IndexBuffer* m_indexBuffer;
};
