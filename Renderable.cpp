#include "Renderable.h"
#include "BaseMesh.h"
#include <Graphics/Material.h>

Renderable::Renderable(GameObject* gameObject, BaseMesh *mesh, Material* material, int order, LayerId layerId) :
	Component("Renderable", gameObject),
	m_mesh(mesh),
	m_material(material),
	m_isActive(true),
	m_order(order),
	m_layerId(layerId)
{
}

Renderable::~Renderable()
{
}

void Renderable::Draw()
{
	assert(m_mesh != NULL);

	m_mesh->Setup();
	m_mesh->Draw();
	m_mesh->Clean();
}

void Renderable::SetMesh(BaseMesh* mesh)
{
	m_mesh = mesh;
}

BaseMesh* Renderable::GetMesh() const
{
	return m_mesh;
}

void Renderable::SetMaterial(Material* material)
{
	m_material = material;
}

Material* Renderable::GetMaterial() const
{
	return m_material;
}

void Renderable::SetActive(bool active)
{
	m_isActive = active;
}

bool Renderable::IsActive() const
{
	return m_isActive;
}

int Renderable::GetOrder() const
{
	return m_order;
}

LayerId Renderable::GetLayerId() const
{
	return m_layerId;
}

