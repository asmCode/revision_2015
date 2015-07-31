#include "SpherePart.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../Camera.h"
#include <Graphics/Material.h>
#include "../Renderable.h"
#include "SpherePartCommands/CommandBase.h"
#include <Math/Animation/QuadOut.h>
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/MathUtils.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"

SpherePart::SpherePart(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_moveOutTime(0.0f),
	m_shiftTime(0.0f),
	m_currentCommand(nullptr)
{
	m_moveOutCurve = new QuadOut<sm::Vec3>();
	m_shiftCurve = new QuadOut<sm::Quat>();

	m_rotatePivot = new GameObject("RotatePivot");
	GetGameObject()->GetTransform().SetParent(&m_rotatePivot->GetTransform());
}

void SpherePart::Awake()
{
	m_basePosition = GetGameObject()->GetTransform().GetLocalPosition();
	m_baseRotation = GetGameObject()->GetTransform().GetLocalRotation();
	m_basePivotRotation = m_rotatePivot->GetTransform().GetLocalRotation();
	m_direction = GetGameObject()->GetTransform().GetPosition().GetNormalized();
	m_material = m_gameObject->GetRenderables()[0]->GetMaterial();
	m_baseColor = m_material->GetParameterVec3("u_color");
}

void SpherePart::Update()
{
	if (m_currentCommand == nullptr && m_commands.size() > 0)
	{
		m_currentCommand = m_commands.front();
		m_currentCommand->SetSpherePart(this);
		m_commands.pop();
	}

	if (m_currentCommand != nullptr)
	{
		if (m_currentCommand->Update())
			m_currentCommand = nullptr;
	}
}

void SpherePart::Open()
{
	m_state = State_Opening;
}

void SpherePart::QueueCommand(CommandBase* command)
{
	//command->SetSpherePart(this);
	m_commands.push(command);
}

Transform* SpherePart::GetPivot() const
{
	return &m_rotatePivot->GetTransform();
}