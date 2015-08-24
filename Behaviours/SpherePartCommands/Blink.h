#pragma once

#include "SphereCommandBase.h"
#include <Math/Vec3.h>

class Blink : public SphereCommandBase
{
public:
	Blink(float duration, const sm::Vec3& color);
	~Blink();

	bool Update();

private:
	float m_duration;
	sm::Vec3 m_color;

	float m_time;

	void SetSpherePart(SpherePart* spherePart);
};
