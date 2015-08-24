#pragma once

#include "../Behaviour.h"
#include <Math/Quat.h>
#include <string>
#include <queue>

class GameObject;
template <typename T > class IAnimationCurve;
class SphereCommandBase;
class Material;
class Transform;

class SpherePart : public Behaviour
{
	friend class PullOut;
	friend class PullIn;
	friend class SlideIn;
	friend class SlideOut;
	friend class RollOut;
	friend class RollIn;
	friend class SphereCommandBase;
	friend class Blink;
	friend class PullOutWithNoise;
	friend class Reset;
	friend class MagnetCommand;

public:
	SpherePart(GameObject* gameObject, const std::string& name);

	void Update();
	void Awake();

	void Open();

	void QueueCommand(SphereCommandBase* command);
	void SetCommand(SphereCommandBase* command);
	void SetCommandParaller(SphereCommandBase* command);

	Transform* GetPivot() const;
	const sm::Vec3& GetDirection() const;

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
	sm::Quat m_basePivotRotation;
	sm::Vec3 m_direction;
	sm::Vec3 m_baseColor;
	Material* m_material;

	GameObject* m_rotatePivot;

	std::queue<SphereCommandBase*> m_commands;
	std::vector<SphereCommandBase*> m_commandsParaller;
	SphereCommandBase* m_currentCommand;
};
