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
	Behaviour(gameObject, name),
	m_depthTexture(NULL),
	m_colorEnabled(true),
	m_depthEnabled(true)
{
}

void RttTest::Awake()
{
	m_camera = (Camera*)ScenesManager::GetInstance()->FindGameObject("kamerka")->GetComponent(Camera::CameraComponentName);

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
			TextureImage* textureImage = (TextureImage*)gameObject->GetComponent("TextureImage");
			textureImage->GetMaterial()->SetParameter("u_tex", m_renderTexture);
		}

		gameObject = ScenesManager::GetInstance()->FindGameObject("kamerka_depth");
		if (gameObject != NULL)
		{
			TextureImage* textureImage = (TextureImage*)gameObject->GetComponent("TextureImage");
			textureImage->GetMaterial()->SetParameter("u_tex", m_depthTexture);
		}
	}

	if (Input::GetKeyUp(KeyCode_R))
	{
		m_camera = (Camera*)ScenesManager::GetInstance()->FindGameObject("kamerka")->GetComponent(Camera::CameraComponentName);

		m_camera->SetRenderToTexture(NULL, NULL);
	}

	if (Input::GetKeyDown(KeyCode_C))
	{
		m_colorEnabled = !m_colorEnabled;
		m_camera->EnableColorBuffer(m_colorEnabled);
	}

	if (Input::GetKeyDown(KeyCode_D))
	{
		m_depthEnabled = !m_depthEnabled;
		m_camera->EnableDepthBuffer(m_depthEnabled);
	}
}

