#include "RttTest.h"
#include "../GameObject.h"
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"
#include "../ScenesManager.h"
#include "../Renderable.h"
#include "../FuturisEngine/BehavioursManager.h"
#include <UserInput/Input.h>
#include <Utils/Random.h>
#include <Graphics/Texture.h>
#include <Graphics/Material.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include <Math/Matrix.h>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

RttTest::RttTest(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void RttTest::Awake()
{
}

void RttTest::Update()
{
	if (Input::GetKeyDown(KeyCode_R))
	{
		m_camera = ScenesManager::GetInstance()->FindGameObject("kamerka")->GetCamera();

		m_renderTexture = new Texture(
			300,
			200,
			32,
			NULL,
			BaseTexture::Wrap_ClampToEdge,
			BaseTexture::Filter_Nearest,
			BaseTexture::Filter_Nearest,
			false);

		m_camera->SetRenderToTexture(m_renderTexture);

		GameObject* gameObject = ScenesManager::GetInstance()->FindGameObject("box4cam1");
		gameObject->GetRenderables()[0]->GetMaterial()->SetParameter("u_diffTex", m_renderTexture);
	}
}

