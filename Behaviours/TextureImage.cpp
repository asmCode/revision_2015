#include "TextureImage.h"
#include "../GameObject.h"
#include "../Renderable.h"
#include "../FuturisEngine/Graphics/Mesh.h"
#include <Graphics/Content/Content.h>
#include <Graphics/Shader.h>
#include <Graphics/Material.h>

using namespace FuturisEngine::Graphics;

TextureImage::TextureImage(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
	RegisterParameter("layer", &m_layer);
	RegisterParameter("texture", &m_textureName);
	RegisterParameter("bounds", &m_bounds);
	RegisterParameter("coords", &m_coords);
}

void TextureImage::Awake()
{
	Mesh* mesh = new Mesh();

	float x = m_bounds.x * 2.0f - 1.0f;
	float y = m_bounds.y * 2.0f - 1.0f;
	float x2 = x + (m_bounds.z * 2.0f);
	float y2 = y + (m_bounds.w * 2.0f);

	sm::Vec3 positions[] =
	{
		sm::Vec3(x, y, 0),
		sm::Vec3(x2, y, 0),
		sm::Vec3(x2, y2, 0),
		sm::Vec3(x, y2, 0)
	};

	sm::Vec2 coords[] =
	{
		sm::Vec2(m_coords.x, m_coords.y),
		sm::Vec2(m_coords.x + m_coords.z, m_coords.y),
		sm::Vec2(m_coords.x + m_coords.z, m_coords.y + m_coords.w),
		sm::Vec2(m_coords.x, m_coords.y + m_coords.w)
	};

	uint32_t indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	mesh->SetIndices(indices, 6);
	mesh->SetVertices(positions, 4);
	mesh->SetCoords1(coords, 4);
	mesh->Apply();

	Texture* texture = Content::Instance->Get<Texture>(m_textureName);
	assert(texture != NULL);

	Shader* shader = Content::Instance->Get<Shader>("TextureImage");
	assert(shader != NULL);

	Material* material = new Material();
	material->SetShader(shader);
	material->SetParameter("u_tex", texture);

	m_gameObject->AddRenderable(new Renderable(m_gameObject, mesh, material, 0, m_gameObject->GetLayerId()));
}

void TextureImage::Update()
{
}
