#pragma once

#include "../Behaviour.h"
#include <Graphics/Point.h>
#include <Math/Quat.h>
#include <string>
#include <stdint.h>

class GameObject;
class Camera;

class Terrain : public Behaviour
{
public:
	Terrain(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

	void NotifyExplosion(const sm::Vec3& position);
	float GetHeight(const sm::Vec3& position);
	bool IsCollision(const sm::Vec3& position);

private:
	const uint32_t* m_indices;
	int m_indicesCount;
	const sm::Vec3* m_vertices;
};
