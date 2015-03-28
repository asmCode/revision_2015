#pragma once

#include "VertexBufferVec3.h"
#include "VertexBufferVec2.h"
#include <stdint.h>

namespace FuturisEngine
{
	namespace Graphics
	{
		class IndexBuffer;
		
		class Mesh
		{
		public:
			Mesh();
			~Mesh();

			void SetIndices(const uint16_t* indices, int count);
			void SetVertices(const sm::Vec3* vertices, int count);
			void SetNormals(const sm::Vec3* normals, int count);
			void SetCoords1(const sm::Vec2* coords, int count);


			const sm::Vec3* GetVertices() const;
			const sm::Vec3* GetNormals() const;
			const sm::Vec2* GetCoords1() const;

			void Apply(bool keepReadable = false);

			int GetVertexCount() const;

			void Draw();

		private:
			static const int DirtyFlagVertex = 1 << 0;
			static const int DirtyFlagNormal = 1 << 1;
			static const int DirtyFlagCoord1 = 1 << 2;

			int m_dirtyFlag;

			IndexBuffer* m_indexBuffer;
			VertexBufferVec3* m_vertexBuffer;
			VertexBufferVec3* m_normalBuffer;
			VertexBufferVec2* m_coord1Buffer;
		};
	}
}

