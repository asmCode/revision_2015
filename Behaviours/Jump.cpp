#include "Jump.h"
#include "../GameObject.h"
#include "../Transform.h"

Jump::Jump(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
	RegisterParameter("speed", &m_speed);
	RegisterParameter("power", &m_power);
}

void Jump::Update()
{
	static float time;

	time += 0.01f;

	m_gameObject->GetTransform().SetPosition(sm::Vec3(0, sinf(time * m_speed) * m_power, 0));
}
