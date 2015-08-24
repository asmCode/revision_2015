#include "SphereCommandBase.h"
#include "../../GameObject.h"
#include "../SpherePart.h"

SphereCommandBase::SphereCommandBase() :
	m_spherePart(nullptr),
	m_transform(nullptr),
	m_pivotTransform(nullptr)
{
}

SphereCommandBase::~SphereCommandBase()
{
}

void SphereCommandBase::SetSpherePart(SpherePart* spherePart)
{
	m_spherePart = spherePart;
	m_transform = &spherePart->GetGameObject()->GetTransform();
	m_pivotTransform = &spherePart->m_rotatePivot->GetTransform();
}

bool SphereCommandBase::Update()
{
	return true;
}

