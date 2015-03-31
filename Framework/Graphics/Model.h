#pragma once

#include <vector>
#include <string>

namespace FuturisEngine { namespace Graphics { class Mesh; } }

class Model
{
public:
	class MeshInfo
	{
	public:
		MeshInfo(const std::string& name, FuturisEngine::Graphics::Mesh* mesh) :
			m_name(name),
			m_mesh(mesh) {}

		const std::string& GetName() const;
		FuturisEngine::Graphics::Mesh* GetMesh() const;

	private:
		std::string m_name;
		FuturisEngine::Graphics::Mesh* m_mesh;
	};

	Model();
	~Model();

	void AddMesh(const std::string& name, FuturisEngine::Graphics::Mesh* mesh);

	const std::vector<MeshInfo*>& GetMeshes();
	
	FuturisEngine::Graphics::Mesh* FindMesh(const std::string &name);

private:
	std::vector<MeshInfo*> m_meshes;
};

