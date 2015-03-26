#include "VertexBufferVec3.h"
#include <GL/glew.h>
#include <stddef.h>
#include <memory>

namespace FuturisEngine
{
	namespace Graphics
	{
		VertexBufferVec3::VertexBufferVec3() :
			m_vboId(0),
			m_count(0),
			m_data(NULL)
		{
		}

		VertexBufferVec3::~VertexBufferVec3()
		{
			if (m_vboId != 0)
				glDeleteBuffers(1, &m_vboId);

			DeleteData();
		}

		void VertexBufferVec3::Setup(int channel)
		{
			assert(m_vboId != 0);

			glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
			glVertexAttribPointer(channel, 3, GL_FLOAT, false, 0, 0);
		}

		void VertexBufferVec3::Apply(bool keepReadable)
		{
			assert(m_vboId != 0);
			assert(m_data != NULL);

			glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(sm::Vec3) * m_count, m_data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			if (!keepReadable)
				DeleteData();
		}

		int VertexBufferVec3::GetCount() const
		{
			return m_count;
		}

		void VertexBufferVec3::SetData(const sm::Vec3* data, int count)
		{
			if (m_vboId == 0)
				Initialize();

			if (m_data == NULL || m_count != count)
			{
				DeleteData();

				m_count = count;
				m_data = new sm::Vec3[m_count];
			}

			memcpy(m_data, data, m_count * sizeof(sm::Vec3));
		}

		const sm::Vec3* VertexBufferVec3::GetData() const
		{
			return m_data;
		}

		void VertexBufferVec3::Initialize()
		{
			assert(m_vboId == 0);

			glGenBuffers(1, &m_vboId);
		}

		void VertexBufferVec3::DeleteData()
		{
			if (m_data != NULL)
			{
				delete[] m_data;
				m_data = NULL;
			}
		}
	}
}

