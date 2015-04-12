#include "SetShaderReplacementTest.h"
#include "../GameObject.h"
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"
#include "../ScenesManager.h"
#include "../Renderable.h"
#include "../FuturisEngine/BehavioursManager.h"
#include "../FuturisEngine/Screen.h"
#include "TextureImage.h"
#include <UserInput/Input.h>
#include <Utils/Random.h>
#include <Graphics/Texture.h>
#include <Graphics/DepthTexture.h>
#include <Graphics/Material.h>
#include <Graphics/Content/Content.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include <Math/Matrix.h>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

SetShaderReplacementTest::SetShaderReplacementTest(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_replacementMaterial1(NULL),
	m_replacementMaterial2(NULL)
{
}

void SetShaderReplacementTest::Awake()
{
	m_camera = ScenesManager::GetInstance()->FindGameObject("kamerka")->GetCamera();
	m_replacementMaterial1 = Content::Instance->Get<Material>("Replace1");
	m_replacementMaterial2 = Content::Instance->Get<Material>("Replace2");
}

void SetShaderReplacementTest::Update()
{
	if (Input::GetKeyDown(KeyCode_0))
	{
		m_camera->SetReplacementMaterial(NULL);
	}

	if (Input::GetKeyDown(KeyCode_Z))
	{
		m_camera->SetReplacementMaterial(m_replacementMaterial1);
	}

	if (Input::GetKeyDown(KeyCode_X))
	{
		m_camera->SetReplacementMaterial(m_replacementMaterial2);
	}
}

