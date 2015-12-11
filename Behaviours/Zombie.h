#pragma once

#include "../Behaviour.h"
#include "../../FuturisEngine/Animation/Animation.h"
#include <Graphics/Point.h>
#include <Math/Quat.h>
#include <string>

class GameObject;
class Camera;
class Terrain;

class Zombie : public Behaviour
{
public:
	Zombie(GameObject* gameObject, const std::string& name);

	void Update();
	void Initialize(Terrain* terrain, const sm::Vec3& startPosition, const sm::Vec3& destination);

private:
	Terrain* m_terrain;
	::Animation* animation;
};
