#include "CustomMesh.h"
#include "../GameObject.h"
#include "../Renderable.h"
#include "../RenderableProxy.h"
#include "../FuturisEngine/Graphics/VertexBufferVec3.h"
#include <UserInput/Input.h>
#include <Graphics/Shader.h>
#include <Graphics/Material.h>
#include <Graphics/Content/Content.h>

using namespace FuturisEngine::Graphics;

CustomMesh::CustomMesh(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void CustomMesh::Awake()
{
	Shader* solidShader = Content::Instance->Get<Shader>("Solid");
	Material* material = new Material();
	material->SetShader(solidShader);
	material->SetParameter("u_color", sm::Vec3(1, 0, 0));

	m_buffer = new VertexBufferVec3();
	sm::Vec3 vertices[3];
	vertices[0] = sm::Vec3(-2, -1, 0);
	vertices[1] = sm::Vec3( 0,  1, 0);
	vertices[2] = sm::Vec3( 2, -1, 0);
	m_buffer->SetData(vertices, 3);
	m_buffer->Apply(true);

	RenderableProxy* renderableProxy = new RenderableProxy(m_buffer);

	Renderable* renderable = new Renderable(m_gameObject, renderableProxy, material);

	m_gameObject->AddRenderable(renderable);
}

void CustomMesh::Update()
{
	if (Input::GetKeyDown(KeyCode_L))
	{
		m_buffer->SetElement(1, sm::Vec3(0, 1, -1));
		m_buffer->Apply(true);
	}
}
