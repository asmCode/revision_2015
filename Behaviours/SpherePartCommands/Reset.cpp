#include "Reset.h"
#include "../SpherePart.h"
#include "../../Transform.h"
#include "../../GameObject.h"
#include "../../FuturisEngine/Time.h"
#include <Graphics/Material.h>
#include <Math/MathUtils.h>
#include <Math/Animation/QuadOut.h>
#include <Math/Animation/QuadIn.h>
#include <Math/Animation/QuarticOut.h>
#include <Math/Animation/QuarticIn.h>

Reset::Reset()
{

}

Reset::~Reset()
{
}

bool Reset::Update()
{
	m_spherePart->m_rotatePivot->GetTransform().SetLocalRotation(m_spherePart->m_basePivotRotation);
	m_transform->SetLocalPosition(m_spherePart->m_basePosition);
	m_transform->SetLocalRotation(m_spherePart->m_baseRotation);

	return true;
}

void Reset::SetSpherePart(SpherePart* spherePart)
{
	this->SphereCommandBase::SetSpherePart(spherePart);
}

