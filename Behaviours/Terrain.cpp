#include "Terrain.h"
#include "../GameObject.h"
#include "../Transform.h"
#include <UserInput/Input.h>
#include <Utils/Random.h>
#include <Math/Quat.h>
#include <Math/Plane.h>
#include <Math/MathUtils.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../ScenesManager.h"
#include "../Camera.h"
#include "../FuturisEngine/Graphics/Mesh.h"
#include "../Renderable.h"
#include "../GraphicsLog.h"

Terrain::Terrain(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

float d;

void Terrain::Update()
{
	/*
	d += Time::DeltaTime * 10.0f;

	//for (int i = 0; i < (m_indicesCount / 3) - 3; i++)
	for (int i = 0; i < (int)d; i++)
	{
		sm::Vec3 triangle[3];
		triangle[0] = m_vertices[m_indices[i * 3 + 0]];
		triangle[1] = m_vertices[m_indices[i * 3 + 1]];
		triangle[2] = m_vertices[m_indices[i * 3 + 2]];

		GraphicsLog::AddSegment(triangle[0], triangle[1]);
		GraphicsLog::AddSegment(triangle[1], triangle[2]);
		GraphicsLog::AddSegment(triangle[2], triangle[0]);	
	}
	*/
}

void Terrain::Awake()
{
	FuturisEngine::Graphics::Mesh* mesh = dynamic_cast<FuturisEngine::Graphics::Mesh*>(m_gameObject->GetRenderables()[0]->GetMesh());

	m_indices = mesh->GetIndices();
	m_indicesCount = mesh->GetIndicesCount();
	m_vertices = mesh->GetVertices();
}

void Terrain::NotifyExplosion(const sm::Vec3& position)
{

}

float Terrain::GetHeight(const sm::Vec3& position)
{
	for (int i = 0; i < m_indicesCount / 3; i++)
	{
		sm::Vec3 triangle[3];
		triangle[0] = m_vertices[m_indices[i * 3 + 0]];
		triangle[1] = m_vertices[m_indices[i * 3 + 1]];
		triangle[2] = m_vertices[m_indices[i * 3 + 2]];
		

		if (MathUtils::IsPointInTriangle(
			sm::Vec3(triangle[0].x, 0, triangle[0].z),
			sm::Vec3(triangle[1].x, 0, triangle[1].z),
			sm::Vec3(triangle[2].x, 0, triangle[2].z),
			sm::Vec3(position.x, 0, position.z)))
		{
			sm::Plane p(((triangle[0] - triangle[1]) * (triangle[0] - triangle[2])).GetNormalized(), triangle[0]);
			sm::Vec3 ip;
			p.GetIntersection(sm::Vec3(0, -1, 0), position, ip);

			return ip.y;
		}
	}

	return 0.0f;
}

bool Terrain::IsCollision(const sm::Vec3& position)
{
	return false;
}

