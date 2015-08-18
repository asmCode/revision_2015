#include "MagnetCommand.h"
#include "../SpherePart.h"
#include "../Magnet.h"
#include "../../Transform.h"
#include "../../GameObject.h"
#include "../../FuturisEngine/Time.h"
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Math/Animation/QuarticOut.h>

MagnetCommand::MagnetCommand(std::vector<Magnet*>& magnets) :
m_magnets(magnets)
{

}

MagnetCommand::~MagnetCommand()
{
}

bool MagnetCommand::Update()
{
	sm::Vec3 direction = m_spherePart->GetGameObject()->GetTransform().GetPosition() - m_spherePart->GetPivot()->GetPosition();
	direction.Normalize();

	float max = 0.0f;
	for (size_t i = 0; i < m_magnets.size(); i++)
	{
		sm::Vec3 toMagnet = m_magnets[i]->GetGameObject()->GetTransform().GetPosition() - m_spherePart->GetPivot()->GetPosition();
		toMagnet.Normalize();

		float dot = sm::Vec3::Dot(direction, toMagnet);
		dot = MathUtils::Clamp(dot, 0.0f, 1.0f);

		dot *= dot * dot;
		dot *= dot * dot;

		if (dot > max)
			max = dot;
	}

	m_spherePart->GetGameObject()->GetTransform().SetLocalPosition(m_spherePart->m_basePosition + direction * 6.0f * max);

	return false;
}

void MagnetCommand::SetSpherePart(SpherePart* spherePart)
{
	this->CommandBase::SetSpherePart(spherePart);
}

