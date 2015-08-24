#include "HeadBang.h"
#include "../../Transform.h"
#include "../../FuturisEngine/Time.h"
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Math/Animation/QuarticOut.h>
#include <Math/Animation/LinearCurve.h>
#include <Math/Animation/Custom/BlinkCurve.h>

namespace MainCameraCommands
{
	HeadBang::HeadBang(float duration, float distance) :
		m_duration(duration),
		m_distance(distance),
		m_time(0.0f)
	{

	}

	HeadBang::~HeadBang()
	{
	}

	void HeadBang::Enter()
	{
		m_forward = -m_subject->GetLookTransform()->GetForward();
		m_dstPos = m_forward * m_distance;
	}

	bool HeadBang::Update()
	{
		m_time = MathUtils::Min(m_duration, m_time + Time::DeltaTime);

		BlinkCurve < sm::Vec3, LinearCurve<sm::Vec3>, QuarticOut<sm::Vec3> > curve(0.1f);

		m_subject->GetLookTransform()->SetLocalPosition(curve.Evaluate(sm::Vec3(0, 0, 0), m_dstPos, m_time / m_duration));

		return m_time == m_duration;
	}
}
