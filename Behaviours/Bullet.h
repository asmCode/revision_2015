#pragma once

#include "../Behaviour.h"
#include <Graphics/Point.h>
#include <Math/Quat.h>
#include <string>

class GameObject;
class Camera;

class Bullet : public Behaviour
{
public:
	Bullet(GameObject* gameObject, const std::string& name);

	void Update();
	void Initialize(const sm::Vec3& startPosition, const sm::Vec3& direction);

private:
};
