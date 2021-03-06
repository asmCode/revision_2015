#include "RevisionTest01.h"
#include "../WallFace.h"
#include "../GameObject.h"
#include "../SceneLoader.h"
#include "../Environment.h"
#include <Utils/Random.h>
#include <Graphics/Model.h>
#include <Graphics/Texture.h>
#include <Graphics/Shader.h>
#include <Math/MathUtils.h>
#include "../DemoController.h"
#include "../GraphicsEngine.h"
#include <Graphics/Framebuffer.h>
#include <Graphics/DepthTexture.h>
#include "../DrawingRoutines.h"
#include <Graphics/Content/Content.h>
#include "../SynchEvent.h"
#include <Utils/Log.h>

#include <UserInput/Input.h>

#include "../Renderable.h"

float faceX;
float faceY;
float faceZ;

float faceRotX;
float faceRotY;
float faceRotZ;

void RevisionTest01::InitializeSubScene()
{
	SceneLoader sceneLoader;

	if (!sceneLoader.LoadFromFile(this, "SynchTestScene"))
	{
		assert(false);
		return;
	}

	Initialize();
}

void RevisionTest01::Initialize()
{
	m_noiseTexIndex = 0;
	m_noiseTexIndexChangeTime = 0.0f;
	m_colorTexture = new Texture(
		FaceResolution,
		FaceResolution,
		32,
		NULL,
		Texture::Wrap_ClampToEdge,
		Texture::Filter_Linear,
		Texture::Filter_Linear,
		false,
		true);

	/*
	m_halfColorTexture = new Texture(
		FaceResolution / 2,
		FaceResolution / 2,
		32,
		NULL,
		Texture::Wrap_ClampToEdge,
		Texture::Filter_Linear,
		Texture::Filter_Linear,
		false);
	*/

	m_blurTexture = new Texture(
		FaceResolution,
		FaceResolution,
		32,
		NULL,
		Texture::Wrap_ClampToEdge,
		Texture::Filter_Linear,
		Texture::Filter_Linear,
		false,
		true);

	m_interBlurTexture = new Texture(
		FaceResolution,
		FaceResolution,
		32,
		NULL,
		Texture::Wrap_ClampToEdge,
		Texture::Filter_Linear,
		Texture::Filter_Linear,
		false,
		true);

	m_depthFramebuffer = new Framebuffer();
	m_depthFramebuffer->Initialize(FaceResolution, FaceResolution);
	m_depthFramebuffer->Setup();
	m_depthFramebuffer->AttachColorTexture(m_colorTexture->GetId());
	m_depthFramebuffer->Validate();

	m_face = Content::Instance->Get<Model>("face");
	assert(m_face != NULL);

	m_wallFace = new WallFace();
	m_wallFace->Initialize(FaceResolution);

	m_room = Content::Instance->Get<Model>("room");
	assert(m_room != NULL);

	m_wall1Tex = Content::Instance->Get<Texture>("wall1");
	assert(m_wall1Tex != NULL);

	m_noiseTexture[0] = Content::Instance->Get<Texture>("tv_noise1");
	assert(m_noiseTexture[0] != NULL);
	m_noiseTexture[1] = Content::Instance->Get<Texture>("tv_noise2");
	assert(m_noiseTexture[1] != NULL);
	m_noiseTexture[2] = Content::Instance->Get<Texture>("tv_noise3");
	assert(m_noiseTexture[2] != NULL);
}

bool RevisionTest01::Update(float time, float deltaTime)
{
	m_noiseTexIndexChangeTime += deltaTime;
	if (m_noiseTexIndexChangeTime > 0.06f)
	{
		m_noiseTexIndexChangeTime = 0;
		m_noiseTexIndex++;
		m_noiseTexIndex %= 3;
	}

	this->BaseScene::Update(time, deltaTime);

	float moveSpeed = deltaTime * 0.1f;
	float rotateSpeed = deltaTime * 1.0f;

	if (Input::GetKey(KeyCode_Up))
		faceY += moveSpeed;
	if (Input::GetKey(KeyCode_Down))
		faceY -= moveSpeed;

	if (Input::GetKey(KeyCode_Right))
		faceX += moveSpeed;
	if (Input::GetKey(KeyCode_Left))
		faceX -= moveSpeed;

	if (Input::GetKey(KeyCode_P))
		faceZ += moveSpeed;
	if (Input::GetKey(KeyCode_L))
		faceZ -= moveSpeed;

	if (Input::GetKey(KeyCode_NumPad6))
		faceRotY += rotateSpeed;
	if (Input::GetKey(KeyCode_NumPad4))
		faceRotY -= rotateSpeed;

	if (Input::GetKey(KeyCode_NumPad2))
		faceRotX += rotateSpeed;
	if (Input::GetKey(KeyCode_NumPad8))
		faceRotX -= rotateSpeed;

	if (Input::GetKey(KeyCode_NumPad7))
		faceRotZ += rotateSpeed;
	if (Input::GetKey(KeyCode_NumPad9))
		faceRotZ -= rotateSpeed;

	Draw();

	return true;
}

void RevisionTest01::Draw()
{	
	if (DemoController::GetInstance() == NULL)
		return;

	if (DemoController::GetInstance()->m_activeCamera == NULL)
		return;

	m_depthFramebuffer->Setup();
	m_depthFramebuffer->AttachColorTexture(m_colorTexture->GetId());

	glDepthMask(true);
	glColorMaski(0, true, true, true, true);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawFace(0.2f);
	//DrawFace(1.0f);

	DemoController::GetInstance()->m_graphicsEngine->Blur(m_colorTexture, m_interBlurTexture, m_blurTexture);

	m_depthFramebuffer->Setup();
	m_depthFramebuffer->AttachColorTexture(m_blurTexture->GetId());
	glDepthMask(true);
	glClear(GL_DEPTH_BUFFER_BIT);

	DrawFace(1.0f, 0.2f);

	glClearColor(0.1f, 0.1f, 0.2f, 0);
	glDepthMask(true);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	DemoController::GetInstance()->m_graphicsEngine->RenderTexture(m_colorTexture->GetId(), 1.0f, 0, 0, FaceResolution, FaceResolution);
	DemoController::GetInstance()->m_graphicsEngine->RenderTexture(m_blurTexture->GetId(), 1.0f, FaceResolution, 0, FaceResolution, FaceResolution);

	glViewport(0, 0, DemoController::GetInstance()->width, DemoController::GetInstance()->height);
	/*
	m_wallFace->Draw(
		m_blurTexture->GetId(),
		m_wall1Tex->GetId(),
		m_noiseTexture[m_noiseTexIndex]->GetId(),
		sm::Matrix::TranslateMatrix(0.0, 2.5f, -9.999f) * sm::Matrix::ScaleMatrix(4.0f, 4.0f, 4.0f),
		DemoController::GetInstance()->m_viewProj,
		DemoController::GetInstance()->m_activeCamera->GetPosition());
		*/
	//m_wallFace->Draw(m_colorTexture, smooth, DemoController::GetInstance()->m_viewProj);

	//DrawingRoutines::DrawWithMaterial(m_room->m_meshParts);
}

void RevisionTest01::DrawFace(float maxDepthValue, float discardMinDepthValue)
{
	sm::Matrix viewProj =
		sm::Matrix::Ortho2DMatrix(-0.6f, 0.6f, -0.6f, 0.6f) *
		sm::Matrix::TranslateMatrix(0, 0, 1);

	sm::Matrix world =
		sm::Matrix::TranslateMatrix(faceX, faceY, faceZ) *
		sm::Matrix::RotateAxisMatrix(faceRotX, 1, 0, 0) *
		sm::Matrix::RotateAxisMatrix(faceRotY, 0, 1, 0) *
		sm::Matrix::RotateAxisMatrix(faceRotZ, 0, 0, 1);

	//m_mainFrame->BindFramebuffer();
	glViewport(0, 0, FaceResolution, FaceResolution);

	GLenum enabledBuffers[1];
	enabledBuffers[0] = GL_COLOR_ATTACHMENT0;
	//enabledBuffers[1] = GL_COLOR_ATTACHMENT1;
	//	glDrawBuffers(1, enabledBuffers);

	
	//glColorMaski(1, true, true, true, true);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

//	DrawingRoutines::DrawDepthByZ(m_face->m_meshParts, world, viewProj, maxDepthValue, discardMinDepthValue);
}

void RevisionTest01::NotifySynchEvent(SynchEvent* synchEvent)
{
}
