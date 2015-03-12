#pragma once

#include "../Behaviour.h"
#include <Graphics/Point.h>
#include <string>

class GameObject;

class FppCamera : public Behaviour
{
public:
	FppCamera(GameObject* gameObject, const std::string& name);

	void Update();

private:
	float m_moveSensitivity;
	float m_rotateSensitivity;

	float m_angleX;
	float m_angleY;
	bool m_rotating;
	sm::Point<int> m_lastCursorPos;

	void UpdatePosition();
	void UpdateRotation();
};
