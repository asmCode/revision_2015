#include "ModelLoader.h"

#include "Model.h"
#include "../../FuturisEngine/Graphics/Mesh.h"

#include <IO\BinaryReader.h>
#include <IO\Path.h>

#include <sstream>

using namespace FuturisEngine::Graphics;

/*
ModelLoader::Vertex::Vertex() :
	m_hasPosition(false),
	m_hasNormal(false),
	m_hasCoord1(false)
{
}

void ModelLoader::Vertex::SetPosition(const sm::Vec3& position)
{
	m_position = position;
	m_hasPosition = true;
}

void ModelLoader::Vertex::SetNormal(const sm::Vec3& normal)
{
	m_normal = normal;
	m_hasNormal = true;
}

void ModelLoader::Vertex::SetCoord1(const sm::Vec2& coord1)
{
	m_coord1 = coord1;
	m_hasCoord1 = true;
}

const sm::Vec3& ModelLoader::Vertex::GetPosition() const
{
	return m_position;
}

const sm::Vec3& ModelLoader::Vertex::GetNormal() const
{
	return m_normal;
}

const sm::Vec2& ModelLoader::Vertex::GetCoord1() const
{
	return m_coord1;
}

bool ModelLoader::Vertex::HasPosition() const
{
	return m_hasPosition;
}

bool ModelLoader::Vertex::HasNormal() const
{
	return m_hasNormal;
}

bool ModelLoader::Vertex::HasCoord1() const
{
	return m_hasCoord1;
}
*/

Model* ModelLoader::LoadFromFile(const std::string &path)
{
	uint8_t *buff;
	uint32_t fileSize;

	if (!Path::GetFileContent(path.c_str(), buff, fileSize))
	{
		assert(false && "couldn't load model file");
		return NULL;
	}

	Model *model = new Model();

	BinaryReader br(buff);

	int meshesCount = br.Read<uint32_t>();

	MeshLoader meshLoader;

	for (uint32_t i = 0; i < meshesCount; i++)
	{
		std::string meshName;
		Mesh *mesh = meshLoader.LoadMesh(br, meshName);
		if (mesh != NULL)
			model->AddMesh(meshName, mesh);
	}

	delete [] buff;

	return model;
}

ModelLoader::MeshLoader::MeshLoader() :
	m_positions(NULL),
	m_normals(NULL),
	m_tangents(NULL),
	m_coords1(NULL),
	m_triangles(NULL)
{
}

ModelLoader::MeshLoader::~MeshLoader()
{
	Dispose();
}

Mesh* ModelLoader::MeshLoader::LoadMesh(BinaryReader &br, std::string& meshName)
{
	Dispose();

	meshName = br.Read<std::string>();

	m_vertexChannel = br.Read<uint8_t>();

	if (m_vertexChannel & FlagVertexChannelVertices)
	{
		m_positionCount = br.Read<uint16_t>();
		m_positions = new sm::Vec3[m_positionCount];
		br.ReadBuffer((char*)m_positions, sizeof(sm::Vec3) * m_positionCount);
	}

	if (m_vertexChannel & FlagVertexChannelNormals)
	{
		m_normalCount = br.Read<uint16_t>();
		m_normals = new sm::Vec3[m_normalCount];
		br.ReadBuffer((char*)m_normals, sizeof(sm::Vec3) * m_normalCount);
	}

	if (m_vertexChannel & FlagVertexChannelTangents)
	{
		m_tangentCount = br.Read<uint16_t>();
		m_tangents = new sm::Vec3[m_tangentCount];
		br.ReadBuffer((char*)m_tangents, sizeof(sm::Vec3) * m_tangentCount);
	}

	if (m_vertexChannel & FlagVertexChannelCoords1)
	{
		m_coord1Count = br.Read<uint16_t>();
		m_coords1 = new sm::Vec2[m_coord1Count];
		br.ReadBuffer((char*)m_coords1, sizeof(sm::Vec2) * m_coord1Count);
	}

	m_triangleCount = br.Read<uint16_t>();
	m_triangles = new Triangle[m_triangleCount];

	for (uint16_t i = 0; i < m_triangleCount; i++)
	{
		if (m_vertexChannel & FlagVertexChannelVertices)
			br.ReadBuffer((char*)m_triangles[i].m_positionIndex, sizeof(uint16_t) * 3);

		if (m_vertexChannel & FlagVertexChannelNormals)
			br.ReadBuffer((char*)m_triangles[i].m_normalIndex, sizeof(uint16_t) * 3);

		if (m_vertexChannel & FlagVertexChannelTangents)
			br.ReadBuffer((char*)m_triangles[i].m_tangentIndex, sizeof(uint16_t) * 3);

		if (m_vertexChannel & FlagVertexChannelCoords1)
			br.ReadBuffer((char*)m_triangles[i].m_coord1Index, sizeof(uint16_t) * 3);
	}

	return BuildMesh();
}

FuturisEngine::Graphics::Mesh* ModelLoader::MeshLoader::BuildMesh()
{
	Mesh* mesh = new Mesh();

	std::vector<sm::Vec3> positions;
	std::vector<sm::Vec3> normals;
	std::vector<sm::Vec3> tangents;
	std::vector<sm::Vec2> coords1;
	std::vector<uint32_t> indices;

	uint32_t vertexIndex = 0;

	for (uint16_t i = 0; i < m_triangleCount; i++)
	{
		for (uint8_t triangleEdge = 0; triangleEdge < 3; triangleEdge++)
		{
			if (m_vertexChannel & FlagVertexChannelVertices)
				positions.push_back(m_positions[m_triangles[i].m_positionIndex[triangleEdge]]);

			if (m_vertexChannel & FlagVertexChannelNormals)
				normals.push_back(m_normals[m_triangles[i].m_normalIndex[triangleEdge]]);

			if (m_vertexChannel & FlagVertexChannelTangents)
				tangents.push_back(m_tangents[m_triangles[i].m_tangentIndex[triangleEdge]]);

			if (m_vertexChannel & FlagVertexChannelCoords1)
				coords1.push_back(m_coords1[m_triangles[i].m_coord1Index[triangleEdge]]);

			indices.push_back(vertexIndex++);
		}
	}

	if (positions.size() > 0)
		mesh->SetVertices(positions.data(), (int)positions.size());
	if (normals.size() > 0)
		mesh->SetNormals(normals.data(), (int)normals.size());
	if (tangents.size() > 0)
		mesh->SetTangents(tangents.data(), (int)tangents.size());
	if (coords1.size() > 0)
		mesh->SetCoords1(coords1.data(), (int)coords1.size());

	mesh->SetIndices(indices.data(), (int)indices.size());

	mesh->Apply(true);

	return mesh;
}

void ModelLoader::MeshLoader::Dispose()
{
	if (m_positions != NULL)
	{
		delete[] m_positions;
		m_positions = NULL;
	}

	if (m_normals != NULL)
	{
		delete[] m_normals;
		m_normals = NULL;
	}

	if (m_tangents != NULL)
	{
		delete[] m_tangents;
		m_tangents = NULL;
	}

	if (m_coords1 != NULL)
	{
		delete[] m_coords1;
		m_coords1 = NULL;
	}

	if (m_triangles != NULL)
	{
		delete[] m_triangles;
		m_triangles = NULL;
	}

	m_positionCount = 0;
	m_normalCount = 0;
	m_tangentCount = 0;
	m_coord1Count = 0;
	m_triangleCount = 0;
}

