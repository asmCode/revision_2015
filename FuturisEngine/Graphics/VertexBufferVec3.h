#pragma once

#include <Math/Vec3.h>
#include <stdint.h>

namespace FuturisEngine
{
	namespace Graphics
	{
		class VertexBufferVec3
		{
		public:
			VertexBufferVec3();
			~VertexBufferVec3();

			void Setup(int channel = 0);
			void Apply(bool keepReadable = false);

			int GetCount() const;
			void SetData(const sm::Vec3* data, int count);
			const sm::Vec3* GetData() const;

		private:
			uint32_t m_vboId;
			int m_count;
			sm::Vec3* m_data;

			void Initialize();
			void DeleteData();
		};
	}
}

