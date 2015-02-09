#pragma once

#include "Static.h"
#include "../GameObject.h"
#include "../SceneElement/CustomSceneElement.h"
#include <stdint.h>
#include <Math/Vec4.h>

class BlinkStatic : public GameObject
{
public:
	BlinkStatic(const std::string& sceneName, SceneElement::CustomSceneElement* data);

	void Update(float time, float seconds);
	void Blink(const sm::Vec4& color);

private:
	Static* m_static;

	sm::Vec4 m_baseColor;
	sm::Vec4 m_blinkColor;
	float m_duration;
	float m_time;

	bool m_isBlinking;
};

