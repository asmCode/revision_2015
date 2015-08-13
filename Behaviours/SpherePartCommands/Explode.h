#pragma once

#include "CommandBase.h"
#include <Math/Vec3.h>
#include <Math/Quat.h>

class Explode : public CommandBase
{
public:
	Explode();
	~Explode();

	bool Update();

private:
	float m_duration;

	sm::Quat m_startRotation;
	sm::Vec3 m_velocity;
	float m_angle;
	sm::Vec3 m_axis;
	float m_spinSpeed;

	void SetSpherePart(SpherePart* spherePart);
};
