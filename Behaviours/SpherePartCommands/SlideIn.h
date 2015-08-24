#pragma once

#include "SphereCommandBase.h"
#include <Math/Vec3.h>
#include <Math/Quat.h>

class SlideIn : public SphereCommandBase
{
public:
	SlideIn(float duration);
	~SlideIn();

	bool Update();

private:
	float m_duration;

	sm::Quat m_startRotation;

	float m_time;

	void SetSpherePart(SpherePart* spherePart);
};
