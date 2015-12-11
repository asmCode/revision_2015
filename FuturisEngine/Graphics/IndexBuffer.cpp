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
			m_count(0),
			m_data(nullptr)
		{
		}

		IndexBuffer::~IndexBuffer()
		{
			if (m_vboId != 0)
				glDeleteBuffers(1, &m_vboId);

			DeleteData();
		}

		void IndexBuffer::SetIndices(const uint32_t* data, int count)
		{
			if (m_vboId == 0)
				Initialize();

			if (m_data == NULL || m_count != count)
			{
				DeleteData();

				m_count = count;
				m_data = new uint32_t[m_count];
			}

			memcpy(m_data, data, m_count * sizeof(uint32_t));
			
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

		const uint32_t* IndexBuffer::GetData() const
		{
			return m_data;
		}
		
		void IndexBuffer::Initialize()
		{
			assert(m_vboId == 0);

			glGenBuffers(1, &m_vboId);
		}

		void IndexBuffer::DeleteData()
		{
			if (m_data != NULL)
			{
				delete[] m_data;
				m_data = NULL;
			}
		}
	}
}

