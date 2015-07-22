#pragma once

#include "../Behaviour.h"
#include <Math/Quat.h>
#include <string>

class GameObject;
template <typename T > class IAnimationCurve;

class SpherePart : public Behaviour
{
public:
	SpherePart(GameObject* gameObject, const std::string& name);

	void Update();
	void Awake();

	void Open();

private:
	enum State
	{
		State_Closed,
		State_Opened,
		State_Opening,
		State_Closing,
	};

	State m_state = State_Closed;

	float MoveOutDuration = 1.0f;
	float ShiftDuration = 1.0f;

	float m_moveOutTime;
	float m_shiftTime;

	IAnimationCurve<sm::Vec3>* m_moveOutCurve;
	IAnimationCurve<sm::Quat>* m_shiftCurve;

	sm::Vec3 m_basePosition;
	sm::Quat m_baseRotation;
	sm::Vec3 m_moveOutPosition;
	sm::Quat m_shiftRotation;

	GameObject* m_rotatePivot;
};
