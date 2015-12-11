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

			void SetIndices(const uint32_t* indices, int count);
			void Draw();
			int GetCount() const;
			const uint32_t* GetData() const;

		private:
			uint32_t m_vboId;
			int m_count;
			uint32_t* m_data;

			void Initialize();
			void DeleteData();
		};
	}
}

