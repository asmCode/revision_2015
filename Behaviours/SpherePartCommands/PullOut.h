#pragma once

#include "CommandBase.h"
#include <Math/Vec3.h>

class PullOut : public CommandBase
{
public:
	PullOut(float duration, float distance);
	~PullOut();

	bool Update();

private:
	float m_duration;
	float m_distance;

	sm::Vec3 m_pullOutPosition;

	float m_time;

	void SetSpherePart(SpherePart* spherePart);
};
