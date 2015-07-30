#pragma once

#include "CommandBase.h"
#include <Math/Vec3.h>

class Blink : public CommandBase
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
