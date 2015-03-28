#pragma once

#include <stdint.h>

namespace FuturisEngine
{
	namespace Graphics
	{
		class IndexBuffer
		{
		public:
			IndexBuffer();
			~IndexBuffer();

			void SetIndices(const uint16_t* indices, int count);
			void Draw();
			int GetCount() const;

		private:
			uint32_t m_vboId;
			int m_count;

			void Initialize();
		};
	}
}

