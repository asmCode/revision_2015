#pragma once

#include "SphereCommandBase.h"
#include <Math/Vec3.h>
#include <Math/Quat.h>

class SlideOut : public SphereCommandBase
{
public:
	SlideOut(float duration, float angle, const sm::Vec3& axis);
	~SlideOut();

	bool Update();

private:
	float m_duration;
	float m_angle;
	sm::Vec3 m_axis;

	sm::Quat m_destinationRotation;

	float m_time;

	void SetSpherePart(SpherePart* spherePart);
};
