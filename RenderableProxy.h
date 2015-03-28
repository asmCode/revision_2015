#pragma once

#include "BaseMesh.h"
#include "../FuturisEngine/Graphics/VertexBufferVec3.h"

class RenderableProxy : public BaseMesh
{
public:
	RenderableProxy(FuturisEngine::Graphics::VertexBufferVec3* buffer);
	virtual ~RenderableProxy();

	void Setup();
	void Draw();
	void Clean();

private:
	FuturisEngine::Graphics::VertexBufferVec3* m_buffer;
};

