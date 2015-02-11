#pragma once

#include "IDrawable.h"
#include <stdint.h>

class PlaneMesh : public IDrawable
{
public:
	PlaneMesh();
	~PlaneMesh();

	bool Initialize(int horiCount, int vertCount);

	// IDrawable implementation
	void Draw();

	static void Setup();
	static void Clean();

private:
	uint32_t m_vertexBufferId;
	uint32_t m_indexBufferId;

	int m_verticesCount;
	int m_indicesCount;

	void CreateIndicesBuffer(int horiCount, int vertCount);
};

