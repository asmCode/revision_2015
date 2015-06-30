#include "Face.h"
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

Face::Face(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_camera(NULL),
	m_depthTexture(NULL),
	m_depthByZMaterial(NULL)
{
	m_depthTexture = new DepthTexture(128, 128);
}

void Face::Awake()
{
	//m_camera = ScenesManager::GetInstance()->FindGameObject("FaceCamera")->GetCamera();
	m_camera = (Camera*)ScenesManager::GetInstance()->FindGameObject("FaceCamera")->GetComponent(Camera::CameraComponentName);
	m_camera->SetOrthoSize(0.5f);
	m_depthByZMaterial = Content::Instance->Get<Material>("DepthByZ");

	m_camera->SetRenderToTexture(NULL, m_depthTexture);
	m_camera->EnableColorBuffer(false);
	m_camera->SetReplacementMaterial(m_depthByZMaterial);

	GameObject* gameObject = ScenesManager::GetInstance()->FindGameObject("kamerka_depth");
	if (gameObject != NULL)
	{
		TextureImage* textureImage = (TextureImage*)gameObject->GetComponent("TextureImage");
		textureImage->GetMaterial()->SetParameter("u_tex", m_depthTexture);
	}
}

void Face::Update()
{
	if (Input::GetKeyDown(KeyCode_0))
	{
	}
}

