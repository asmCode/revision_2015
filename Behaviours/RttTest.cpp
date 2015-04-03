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
			Screen::Width,
			Screen::Height,
			32,
			NULL,
			BaseTexture::Wrap_ClampToEdge,
			BaseTexture::Filter_Linear,
			BaseTexture::Filter_Linear,
			false);

		m_camera->SetRenderToTexture(m_renderTexture);

		GameObject* gameObject = ScenesManager::GetInstance()->FindGameObject("kamerka_output");
		if (gameObject != NULL)
		{
			TextureImage* textureImage = (TextureImage*)gameObject->GetBehaviour("TextureImage");
			textureImage->GetMaterial()->SetParameter("u_tex", m_renderTexture);
		}
	}

	if (Input::GetKeyUp(KeyCode_R))
	{
		m_camera = ScenesManager::GetInstance()->FindGameObject("kamerka")->GetCamera();

		m_camera->SetRenderToTexture(NULL);
	}
}

