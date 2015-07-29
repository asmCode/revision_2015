#pragma once

#include "CommandBase.h"
#include <Math/Vec3.h>
#include <Math/Quat.h>

class RollOut : public CommandBase
{
public:
	RollOut(float duration, float angle);
	~RollOut();

	bool Update();

private:
	float m_duration;
	float m_angle;

	sm::Quat m_destinationRotation;

	float m_time;

	void SetSpherePart(SpherePart* spherePart);
};
