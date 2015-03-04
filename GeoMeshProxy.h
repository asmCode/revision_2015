#pragma once

#include "BaseMesh.h"

class MeshPart;

class GeoMeshProxy : public BaseMesh
{
public:
	GeoMeshProxy(MeshPart* meshPart);
	virtual ~GeoMeshProxy();

	void Setup();
	void Draw();
	void Clean();

private:
	MeshPart* m_meshPart;
};
