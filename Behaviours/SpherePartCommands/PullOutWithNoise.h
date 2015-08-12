#pragma once

#include "CommandBase.h"
#include <Math/Vec3.h>
#include <Math/Quat.h>

class PullOutWithNoise : public CommandBase
{
public:
	PullOutWithNoise(float duration, float distance);
	~PullOutWithNoise();

	bool Update();

private:
	float m_duration;
	float m_distance;

	sm::Vec3 m_initialPosition;
	sm::Vec3 m_pullOutPosition;

	sm::Quat m_initialRotation;
	sm::Quat m_destinationRotation;

	float m_time;

	void SetSpherePart(SpherePart* spherePart);
};
