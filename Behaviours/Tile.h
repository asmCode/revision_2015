#pragma once

#include "../Behaviour.h"
#include <Math/Quat.h>
#include <Math/Vec3.h>
#include <string>

class GameObject;

class Tile : public Behaviour
{
public:
	Tile(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

	void Blow();

	bool IsDetached() const;

private:
	sm::Quat m_baseRotate;

	sm::Vec3 m_velocity;

	float m_angle;
	sm::Vec3 m_axis;
	float m_spinSpeed;

	bool m_isDetached;
};
