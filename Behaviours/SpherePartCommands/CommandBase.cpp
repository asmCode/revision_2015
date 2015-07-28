#include "CommandBase.h"
#include "../../GameObject.h"
#include "../SpherePart.h"

CommandBase::CommandBase() :
	m_spherePart(nullptr),
	m_transform(nullptr),
	m_pivotTransform(nullptr)
{
}

CommandBase::~CommandBase()
{
}

void CommandBase::SetSpherePart(SpherePart* spherePart)
{
	m_spherePart = spherePart;
	m_transform = &spherePart->GetGameObject()->GetTransform();
	m_pivotTransform = &spherePart->m_rotatePivot->GetTransform();
}

bool CommandBase::Update()
{
	return true;
}

