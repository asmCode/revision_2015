#pragma once

#include "CommandBase.h"
#include <Math/Vec3.h>

class PullIn : public CommandBase
{
public:
	PullIn(float duration);
	~PullIn();

	bool Update();

private:
	float m_duration;

	sm::Vec3 m_startPosition;

	float m_time;

	void SetSpherePart(SpherePart* spherePart);
};
