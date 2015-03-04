#include "MeshPart.h"

#include "VertexInformation.h"

#include "Mesh.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

#include <GL/glew.h>

MeshPart::MeshPart(int verticesCount, void *vertices, Mesh *mesh, uint8_t vertexType) :
	m_vertexType(vertexType),
	m_parentNode(NULL),
	m_lightmap(NULL),
	m_alwaysHide(false)
{
	bbox = new BoundingBox();
	(*bbox) = BoundingBox::FromVertices(vertices, verticesCount, vertexType, 1.0f);
	bsphere = new BoundingSphere();
	(*bsphere) = BoundingSphere::FromBBox(*bbox);
	
	visible = true;
	isAlwaysVisible = false;

	this->mesh = mesh;
	this ->verticesCount = verticesCount;
	this ->vertices = vertices;
	
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, verticesCount * VertexInformation::GetStride(m_vertexType), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	material = NULL;
}

bool& MeshPart::IsAlvaysVisible()
{
	return isAlwaysVisible;
}

MeshPart::~MeshPart()
{
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glDeleteBuffersARB(1, &vboId);

	delete [] vertices;
	delete bbox;
	delete bsphere;
}

void MeshPart::Setup()
{
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
	SetupVertexPointers();
}

void MeshPart::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}

void MeshPart::Clean()
{
	if (m_vertexType == VertexType::PN)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(3);
	}
	else if (m_vertexType == VertexType::PCN)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(3);
	}
	else if (m_vertexType == VertexType::PC2N)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
	}
	else if (m_vertexType == VertexType::PCNT)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
	}
	else if (m_vertexType == VertexType::PC2NT)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
	}

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

void MeshPart::SetMaterial(Material *material)
{
	this ->material = material;
}

Material *MeshPart::GetMaterial()
{
	return material;
}

int MeshPart::GetVerticesCount()
{
	return verticesCount;
}

const void* MeshPart::GetVertices()
{
	return vertices;
}

void MeshPart::SetVisibility(bool visible)
{
	this->visible = visible;
}

bool MeshPart::IsVisible() const
{
	return visible && !m_alwaysHide;
}

void MeshPart::SetupVertexPointers()
{
	/*
	0 - Position
	1 - Coords1
	2 - Coords2
	3 - Normal
	4 - Coords1
	5 - Tangent
	*/

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
	glDisableVertexAttribArray(7);

	if (m_vertexType == VertexType::PN)
	{
		uint32_t stride = VertexInformation::GetStride(m_vertexType);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Position)));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Normal)));
		glEnableVertexAttribArray(3);
	}
	else if (m_vertexType == VertexType::PCN)
	{
		uint32_t stride = VertexInformation::GetStride(m_vertexType);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Position)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Coords1)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Normal)));
		glEnableVertexAttribArray(3);
	}
	else if (m_vertexType == VertexType::PC2N)
	{
		uint32_t stride = VertexInformation::GetStride(m_vertexType);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Position)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Coords1)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Coords2)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Normal)));
		glEnableVertexAttribArray(3);
	}
	else if (m_vertexType == VertexType::PCNT)
	{
		uint32_t stride = VertexInformation::GetStride(m_vertexType);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Position)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Coords1)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Normal)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Tangent)));
		glEnableVertexAttribArray(4);
	}
	else if (m_vertexType == VertexType::PC2NT)
	{
		uint32_t stride = VertexInformation::GetStride(m_vertexType);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Position)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Coords1)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Coords2)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Normal)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(VertexInformation::GetOffset(m_vertexType, VertexAttrib::Tangent)));
		glEnableVertexAttribArray(4);
	}
	else
	{
		int f = 0;
	}
}
