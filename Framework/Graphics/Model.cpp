#include "Model.h"
#include "../../FuturisEngine/Graphics/Mesh.h"

using namespace FuturisEngine::Graphics;

const std::string& Model::MeshInfo::GetName() const
{
	return m_name;
}

FuturisEngine::Graphics::Mesh* Model::MeshInfo::GetMesh() const
{
	return m_mesh;
}

Model::Model()
{
}

Model::~Model()
{
	for (int i = 0; i < (int)m_meshes.size(); i++)
		delete m_meshes[i]->GetMesh();
}

void Model::AddMesh(const std::string& name, Mesh* mesh)
{
	m_meshes.push_back(new MeshInfo(name, mesh));
}

const std::vector<Model::MeshInfo*>& Model::GetMeshes()
{
	return m_meshes;
}

Mesh* Model::FindMesh(const std::string &name)
{
	for (unsigned i = 0; i < m_meshes.size(); i++)
		if (m_meshes[i]->GetName() == name)
			return m_meshes[i]->GetMesh();

	return NULL;
}

