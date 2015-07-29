#pragma once

#include "CommandBase.h"
#include <Math/Vec3.h>
#include <Math/Quat.h>

class SlideIn : public CommandBase
{
public:
	SlideIn(float duration);
	~SlideIn();

	bool Update();

private:
	float m_duration;

	sm::Quat m_baseRotation;
	sm::Quat m_startRotation;

	float m_time;

	void SetSpherePart(SpherePart* spherePart);
};
