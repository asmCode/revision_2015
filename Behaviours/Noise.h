#pragma once

#include "../Behaviour.h"
#include <Math/Vec3.h>
#include <Math/Quat.h>
#include <string>

class GameObject;
//template<float> class IAnimationCurve;

class Noise : public Behaviour
{
public:
	Noise(GameObject* gameObject, const std::string& name);

	void Update();

	void TranslationNoise(float speed, float range);
	void RotationNoise(float speed, float angle);

private:
	float m_translationSpeed;
	float m_translationRange;
	float m_rotationSpeed;
	float m_rotationAngle;

	sm::Vec3 m_translateFrom;
	sm::Vec3 m_translateTo;
	float m_translateTime;

	sm::Quat m_rotateFrom;
	sm::Quat m_rotateTo;
	float m_rotateTime;

	sm::Vec3 GetNextTranslation();
	void GetNextRotation();
};
