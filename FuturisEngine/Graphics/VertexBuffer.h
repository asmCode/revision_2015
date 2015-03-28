#pragma once

#include <stdint.h>
#include <GL/glew.h>
#include <stddef.h>
#include <memory>
#include <assert.h>

namespace FuturisEngine
{
	namespace Graphics
	{
		template <typename T, int C>
		class VertexBuffer
		{
		public:
			VertexBuffer() :
				m_vboId(0),
				m_count(0),
				m_data(NULL)
			{
			}

			~VertexBuffer()
			{
				if (m_vboId != 0)
					glDeleteBuffers(1, &m_vboId);

				DeleteData();
			}

			void Setup(int index)
			{
				assert(m_vboId != 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, C, GL_FLOAT, false, 0, 0);
			}

			void Apply(bool keepReadable = false)
			{
				assert(m_vboId != 0);
				assert(m_data != NULL);

				glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
				glBufferData(GL_ARRAY_BUFFER, sizeof(T) * m_count, m_data, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				if (!keepReadable)
					DeleteData();
			}

			void TmpDraw()
			{
				glDrawArrays(GL_TRIANGLES, 0, m_count);
			}

			int GetCount() const
			{
				return m_count;
			}

			void SetData(const T* data, int count)
			{
				if (m_vboId == 0)
					Initialize();

				if (m_data == NULL || m_count != count)
				{
					DeleteData();

					m_count = count;
					m_data = new T[m_count];
				}

				memcpy(m_data, data, m_count * sizeof(T));
			}

			void SetElement(int index, const T& element)
			{
				assert(m_data != NULL);
				assert(index < m_count);

				*(m_data + index) = element;
			}

			const T* GetData() const
			{
				return m_data;
			}

		private:
			uint32_t m_vboId;
			int m_count;
			T* m_data;

			void Initialize()
			{
				assert(m_vboId == 0);

				glGenBuffers(1, &m_vboId);
			}

			void DeleteData()
			{
				if (m_data != NULL)
				{
					delete[] m_data;
					m_data = NULL;
				}
			}
		};
	}
}

