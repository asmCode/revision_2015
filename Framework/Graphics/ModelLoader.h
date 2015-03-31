#pragma once

#include <Math/Vec2.h>
#include <Math/Vec3.h>
#include <string>
#include <map>
#include <stdint.h>

class Model;
namespace FuturisEngine { namespace Graphics { class Mesh; } }
class BinaryReader;

class ModelLoader
{
public:
	Model* LoadFromFile(const std::string &path);

private:
	/*
	class Vertex
	{
	public:
		Vertex();

		void SetPosition(const sm::Vec3& position);
		void SetNormal(const sm::Vec3& normal);
		void SetCoord1(const sm::Vec2& coord1);

		const sm::Vec3& GetPosition() const;
		const sm::Vec3& GetNormal() const;
		const sm::Vec2& GetCoord1() const;

		bool HasPosition() const;
		bool HasNormal() const;
		bool HasCoord1() const;

	private:
		sm::Vec3 m_position;
		sm::Vec3 m_normal;
		sm::Vec2 m_coord1;

		bool m_hasPosition;
		bool m_hasNormal;
		bool m_hasCoord1;
	};
	*/

	/*
	class Vertex
	{
	public:
		uint16_t m_positionIndex;
		uint16_t m_normalIndex;
		uint16_t m_coord1Index;
	};
	*/

	class Triangle
	{
	public:
		uint16_t m_positionIndex[3];
		uint16_t m_normalIndex[3];
		uint16_t m_coord1Index[3];
	};

	class MeshLoader
	{
	public:
		MeshLoader();
		~MeshLoader();

		FuturisEngine::Graphics::Mesh* LoadMesh(BinaryReader &br, std::string& meshName);

	private:
		static const uint8_t FlagVertexChannelVertices = 1 << 0;
		static const uint8_t FlagVertexChannelNormals = 1 << 1;
		static const uint8_t FlagVertexChannelCoords1 = 1 << 2;
		//std::vector<Vertex> m_vertices;

		uint8_t m_vertexChannel;

		uint16_t m_positionCount;
		sm::Vec3* m_positions;
		uint16_t m_normalCount;
		sm::Vec3* m_normals;
		uint16_t m_coord1Count;
		sm::Vec2* m_coords1;
		uint16_t m_triangleCount;
		Triangle* m_triangles;

		FuturisEngine::Graphics::Mesh* BuildMesh();

		void Dispose();
	};
};

