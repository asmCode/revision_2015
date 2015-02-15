#include "PlaneMesh.h"

#include <Math/Vec3.h>
#include <GL/glew.h>
#include <assert.h>

PlaneMesh::PlaneMesh() :
	m_vertexBufferId(0),
	m_indexBufferId(0)
{

}

PlaneMesh::~PlaneMesh()
{

}

bool PlaneMesh::Initialize(int horiCount, int vertCount)
{
	assert(m_vertexBufferId == 0);
	assert(m_indexBufferId == 0);
	assert(horiCount >= 2);
	assert(vertCount >= 2);

	m_verticesCount = horiCount * vertCount;

	sm::Vec3* vertices = new sm::Vec3[m_verticesCount];

	float faceWidth = 1.0f / (float)(horiCount - 1);
	float faceHeight = 1.0f / (float)(vertCount - 1);

	float x = -0.5f;
	float y = -0.5f;
	int index = 0;

	for (int iy = 0; iy < vertCount; iy++)
	{
		for (int ix = 0; ix < horiCount; ix++)
		{
			vertices[index++].Set(x, y, 0.0f);

			x += faceWidth;
		}

		x = -0.5f;
		y += faceHeight;
	}

	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sm::Vec3) * m_verticesCount, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] vertices;

	CreateIndicesBuffer(horiCount, vertCount);

	return true;
}

void PlaneMesh::CreateIndicesBuffer(int horiCount, int vertCount)
{
	glPrimitiveRestartIndex(65535);
	glEnable(GL_PRIMITIVE_RESTART);

	m_indicesCount = horiCount * 2 * (vertCount - 1) + vertCount - 2;

	uint16_t* indexBuffer = new uint16_t[m_indicesCount];

	int index = 0;

	for (int y = 0; y < vertCount - 1; y++)
	{
		for (int x = 0; x < horiCount; x++)
		{
			indexBuffer[index++] = x + y * horiCount;
			indexBuffer[index++] = x + y * horiCount + horiCount;
		}

		if (y != vertCount - 2)
			indexBuffer[index++] = 65535;
	}

	glGenBuffers(1, &m_indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * m_indicesCount, indexBuffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] indexBuffer;
}

void PlaneMesh::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
	glDrawElements(GL_TRIANGLE_STRIP, m_indicesCount, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void PlaneMesh::Setup()
{
	glEnableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
}

void PlaneMesh::Clean()
{
	glDisableVertexAttribArray(0);
}
