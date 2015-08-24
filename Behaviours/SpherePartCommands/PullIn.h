#pragma once

#include "SphereCommandBase.h"
#include <Math/Vec3.h>
#include <Math/Quat.h>

class PullIn : public SphereCommandBase
{
public:
	PullIn(float duration);
	~PullIn();

	bool Update();

private:
	float m_duration;

	sm::Vec3 m_startPosition;
	sm::Quat m_startRotation;

	float m_time;

	void SetSpherePart(SpherePart* spherePart);
};
