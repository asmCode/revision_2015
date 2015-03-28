#include "RenderableProxy.h"
#include "FuturisEngine/Graphics/VertexBufferVec3.h"

using namespace FuturisEngine::Graphics;

RenderableProxy::RenderableProxy(VertexBufferVec3* buffer) :
	m_buffer(buffer)
{

}

RenderableProxy::~RenderableProxy()
{

}

void RenderableProxy::Setup()
{
	m_buffer->Setup();
}

void RenderableProxy::Draw()
{
	m_buffer->TmpDraw();
}

void RenderableProxy::Clean()
{
}
