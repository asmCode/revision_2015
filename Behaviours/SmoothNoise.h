#pragma once

#include "../Behaviour.h"
#include <Math/Animation/AnimationCurve.h>
#include <Math/Vec3.h>
#include <Math/Quat.h>
#include <string>

class GameObject;

class SmoothNoise : public Behaviour
{
public:
	SmoothNoise(GameObject* gameObject, const std::string& name);

	void Update();

	void TranslationNoise(float speed, float range);
	void RotationNoise(float speed, float angle);

private:
	float m_time;
	float m_posSpeed;
	float m_rotSpeed;

	AnimationCurve<sm::Vec3> m_posCurve;
	AnimationCurve<sm::Quat> m_rotCurve;
};
