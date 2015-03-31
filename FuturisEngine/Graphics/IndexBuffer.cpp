#include "IndexBuffer.h"
#include <GL/glew.h>
#include <stddef.h>
#include <memory>
#include <assert.h>

namespace FuturisEngine
{
	namespace Graphics
	{
		IndexBuffer::IndexBuffer() :
			m_vboId(0),
			m_count(0)
		{
		}

		IndexBuffer::~IndexBuffer()
		{
			if (m_vboId != 0)
				glDeleteBuffers(1, &m_vboId);
		}

		void IndexBuffer::SetIndices(const uint32_t* data, int count)
		{
			if (m_vboId == 0)
				Initialize();

			m_count = count;
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void IndexBuffer::Draw()
		{
			assert(m_vboId != 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboId);
			glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, 0);
		}

		int IndexBuffer::GetCount() const
		{
			return m_count;
		}

		void IndexBuffer::Initialize()
		{
			assert(m_vboId == 0);

			glGenBuffers(1, &m_vboId);
		}
	}
}

