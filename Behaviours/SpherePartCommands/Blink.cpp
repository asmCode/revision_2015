#include "Blink.h"
#include "../SpherePart.h"
#include "../../Transform.h"
#include "../../FuturisEngine/Time.h"
#include <Graphics/Material.h>
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Math/Animation/QuadIn.h>
#include <Math/Animation/QuarticOut.h>
#include <Math/Animation/QuarticIn.h>

extern bool StopBlink;

Blink::Blink(float duration, const sm::Vec3& color) :
m_duration(duration),
m_color(color),
m_time(0.0f)
{
	StopBlink = false;
}

Blink::~Blink()
{
}

bool Blink::Update()
{
	m_time = MathUtils::Min(m_duration, m_time + Time::DeltaTime);

	QuadIn<sm::Vec3> curve;

	if (!StopBlink)
		m_spherePart->m_material->SetParameter("u_color", curve.Evaluate(m_color, m_spherePart->m_baseColor, m_time / m_duration));

	return m_time == m_duration;
}

void Blink::SetSpherePart(SpherePart* spherePart)
{
	this->SphereCommandBase::SetSpherePart(spherePart);
}

