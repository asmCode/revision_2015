#include "SpherePart.h"
#include "../ScenesManager.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../Camera.h"
#include <Graphics/Material.h>
#include "../Renderable.h"
#include "SpherePartCommands/SphereCommandBase.h"
#include <Math/Animation/QuadOut.h>
#include <UserInput/Input.h>
#include <Math/Quat.h>
#include <Math/MathUtils.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"
#include <Graphics/Content/Content.h>

SpherePart::SpherePart(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_moveOutTime(0.0f),
	m_shiftTime(0.0f),
	m_currentCommand(nullptr)
{
	m_moveOutCurve = new QuadOut<sm::Vec3>();
	m_shiftCurve = new QuadOut<sm::Quat>();

	m_rotatePivot = new GameObject("RotatePivot");
	m_rotatePivot->GetTransform().SetParent(GetGameObject()->GetTransform().GetParent());
	m_rotatePivot->GetTransform().SetLocalPosition(sm::Vec3(0, 0, 0));
	m_rotatePivot->GetTransform().SetLocalRotation(sm::Quat::FromAngleAxis(0.0f, sm::Vec3(0, 0, 0)));
	m_rotatePivot->GetTransform().SetLocalScale(sm::Vec3(1, 1, 1));
	GetGameObject()->GetTransform().SetParent(&m_rotatePivot->GetTransform());

	m_direction = GetGameObject()->GetTransform().GetLocalPosition().GetNormalized();
}

void SpherePart::Awake()
{
	m_basePosition = GetGameObject()->GetTransform().GetLocalPosition();
	m_baseRotation = GetGameObject()->GetTransform().GetLocalRotation();
	m_basePivotRotation = m_rotatePivot->GetTransform().GetLocalRotation();

	m_material = Content::Instance->Get<Material>("glow");
	//m_baseColor = m_material->GetParameterVec3("u_color");
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

	std::vector<SphereCommandBase*> commands;
	commands.insert(commands.begin(), m_commandsParaller.begin(), m_commandsParaller.end());
	m_commandsParaller.clear();
	for (size_t i = 0; i < commands.size(); i++)
	{
		SphereCommandBase* command = commands[i];
		command->SetSpherePart(this);
		if (!command->Update())
			m_commandsParaller.push_back(command);
	}
}

void SpherePart::Open()
{
	m_state = State_Opening;
}

void SpherePart::QueueCommand(SphereCommandBase* command)
{
	//command->SetSpherePart(this);
	m_commands.push(command);
}

void SpherePart::SetCommand(SphereCommandBase* command)
{
	m_currentCommand = nullptr;

	while (!m_commands.empty())
		m_commands.pop();

	m_commands.push(command);
}

void SpherePart::SetCommandParaller(SphereCommandBase* command)
{
	m_commandsParaller.push_back(command);
}

Transform* SpherePart::GetPivot() const
{
	return &m_rotatePivot->GetTransform();
}

const sm::Vec3& SpherePart::GetDirection() const
{
	return m_direction;
}
