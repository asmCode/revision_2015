#include "Mesh.h"
#include "IndexBuffer.h"
#include <GL/glew.h>
#include <stddef.h>
#include <memory>
#include <assert.h>

namespace FuturisEngine
{
	namespace Graphics
	{
		Mesh::Mesh() :
			m_dirtyFlag(0),
			m_indexBuffer(NULL),
			m_vertexBuffer(NULL),
			m_normalBuffer(NULL),
			m_coord1Buffer(NULL)
		{

		}

		Mesh::~Mesh()
		{
			if (m_indexBuffer != NULL)
				delete m_indexBuffer;

			if (m_vertexBuffer != NULL)
				delete m_vertexBuffer;

			if (m_normalBuffer != NULL)
				delete m_normalBuffer;

			if (m_coord1Buffer != NULL)
				delete m_coord1Buffer;
		}

		void Mesh::SetIndices(const uint32_t* vertices, int count)
		{
			if (m_indexBuffer == NULL)
				m_indexBuffer = new IndexBuffer();

			m_indexBuffer->SetIndices(vertices, count);
		}

		void Mesh::SetVertices(const sm::Vec3* vertices, int count)
		{
			if (m_vertexBuffer == NULL)
				m_vertexBuffer = new VertexBufferVec3();

			m_vertexBuffer->SetData(vertices, count);

			m_dirtyFlag |= DirtyFlagVertex;
		}

		void Mesh::SetNormals(const sm::Vec3* normals, int count)
		{
			if (m_normalBuffer == NULL)
				m_normalBuffer = new VertexBufferVec3();

			m_normalBuffer->SetData(normals, count);

			m_dirtyFlag |= DirtyFlagNormal;
		}

		void Mesh::SetCoords1(const sm::Vec2* coords, int count)
		{
			if (m_coord1Buffer == NULL)
				m_coord1Buffer = new VertexBufferVec2();

			m_coord1Buffer->SetData(coords, count);

			m_dirtyFlag |= DirtyFlagCoord1;
		}

		const sm::Vec3* Mesh::GetVertices() const
		{
			return m_vertexBuffer != NULL ? m_vertexBuffer->GetData() : NULL;
		}

		const sm::Vec3* Mesh::GetNormals() const
		{
			return m_normalBuffer != NULL ? m_normalBuffer->GetData() : NULL;
		}

		const sm::Vec2* Mesh::GetCoords1() const
		{
			return m_coord1Buffer != NULL ? m_coord1Buffer->GetData() : NULL;
		}

		void Mesh::Apply(bool keepReadable)
		{
			if ((m_dirtyFlag & DirtyFlagVertex) && m_vertexBuffer != NULL)
				m_vertexBuffer->Apply(keepReadable);

			if ((m_dirtyFlag & DirtyFlagNormal) && m_normalBuffer != NULL)
				m_normalBuffer->Apply(keepReadable);

			if ((m_dirtyFlag & DirtyFlagCoord1) && m_coord1Buffer != NULL)
				m_coord1Buffer->Apply(keepReadable);

			m_dirtyFlag = false;
		}

		int Mesh::GetVertexCount() const
		{
			return m_vertexBuffer != NULL ? m_vertexBuffer->GetCount() : 0;
		}

		void Mesh::Draw()
		{
			assert(m_indexBuffer != NULL);

			if (m_vertexBuffer != NULL)
				m_vertexBuffer->Setup(VertexBufferIndex);

			if (m_normalBuffer != NULL)
				m_normalBuffer->Setup(NormalBufferIndex);

			if (m_coord1Buffer != NULL)
				m_coord1Buffer->Setup(Coord1BufferIndex);

			m_indexBuffer->Draw();
		}
	}
}

