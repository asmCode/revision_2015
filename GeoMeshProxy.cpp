#include "GeoMeshProxy.h"
#include <Graphics/MeshPart.h>

class MeshPart;

GeoMeshProxy::GeoMeshProxy(MeshPart* meshPart) :
	m_meshPart(meshPart)
{

}

GeoMeshProxy::~GeoMeshProxy()
{

}

void GeoMeshProxy::Setup()
{
	m_meshPart->Setup();
}

void GeoMeshProxy::Draw()
{
	m_meshPart->Draw();
}

void GeoMeshProxy::Clean()
{
	m_meshPart->Clean();
}
