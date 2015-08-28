#pragma once

#include "../Component.h"
#include "../FuturisEngine/LayerId.h"
#include <Math/Matrix.h>

class BaseMesh;
class Material;
class GameObject;

class Renderable : public Component
{
public:
	Renderable(
		GameObject* gameObject,
		BaseMesh *mesh,
		Material* material,
		int order = 0,
		LayerId layerId = LayerId_0);

	virtual ~Renderable();

	virtual void Draw();

	void SetMesh(BaseMesh* mesh);
	BaseMesh* GetMesh() const;

	void SetMaterial(Material* material);
	Material* GetMaterial() const;

	void SetActive(bool active);
	bool IsActive() const;
	int GetOrder() const;
	void SetLayerId(LayerId layerId);
	LayerId GetLayerId() const;

private:
	BaseMesh* m_mesh;
	Material* m_material;

	bool m_isActive;
	int m_order;
	LayerId m_layerId;
};

