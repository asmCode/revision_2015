#include "RttTest.h"
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
	m_camera = ScenesManager::GetInstance()->FindGameObject("kamerka")->GetCamera();

	m_renderTexture = new Texture(
		Screen::Width,
		Screen::Height,
		32,
		NULL,
		BaseTexture::Wrap_ClampToEdge,
		BaseTexture::Filter_Linear,
		BaseTexture::Filter_Linear,
		false);

	m_depthTexture = new DepthTexture(Screen::Width, Screen::Height);
}

void RttTest::Update()
{
	if (Input::GetKeyDown(KeyCode_R))
	{
		m_camera->SetRenderToTexture(m_renderTexture, m_depthTexture);

		GameObject* gameObject = ScenesManager::GetInstance()->FindGameObject("kamerka_color");
		if (gameObject != NULL)
		{
			TextureImage* textureImage = (TextureImage*)gameObject->GetBehaviour("TextureImage");
			textureImage->GetMaterial()->SetParameter("u_tex", m_renderTexture);
		}

		gameObject = ScenesManager::GetInstance()->FindGameObject("kamerka_depth");
		if (gameObject != NULL)
		{
			TextureImage* textureImage = (TextureImage*)gameObject->GetBehaviour("TextureImage");
			textureImage->GetMaterial()->SetParameter("u_tex", m_depthTexture);
		}
	}

	if (Input::GetKeyUp(KeyCode_R))
	{
		m_camera = ScenesManager::GetInstance()->FindGameObject("kamerka")->GetCamera();

		m_camera->SetRenderToTexture(NULL, NULL);
	}
}

