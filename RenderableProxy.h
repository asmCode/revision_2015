#pragma once

#include "BaseMesh.h"

namespace FuturisEngine { namespace Graphics { class VertexBufferVec3; } }

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
