#include "RevisionTest01.h"
#include "../WallFace.h"
#include "../GameObject.h"
#include "../Materials/GlowTransparencySpecullar.h"
#include "../SceneLoader.h"
#include "../Environment.h"
#include <Utils/Randomizer.h>
#include <Graphics/MeshPart.h>
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

#include "../Renderable.h"

Texture* smooth;

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
	m_colorTexture = new Texture(
		FaceResolution,
		FaceResolution,
		32,
		NULL,
		Texture::Wrap_ClampToEdge,
		Texture::Filter_Linear,
		Texture::Filter_Linear,
		false);

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
		false);

	m_interBlurTexture = new Texture(
		FaceResolution,
		FaceResolution,
		32,
		NULL,
		Texture::Wrap_ClampToEdge,
		Texture::Filter_Linear,
		Texture::Filter_Linear,
		false);

	m_depthFramebuffer = new Framebuffer();
	m_depthFramebuffer->Initialize(FaceResolution, FaceResolution, 32);
	m_depthFramebuffer->BindFramebuffer();
	m_depthFramebuffer->AttachColorTexture(m_colorTexture->GetId());
	m_depthFramebuffer->Validate();

	m_face = Content::Instance->Get<Model>("face");
	assert(m_face != NULL);

	smooth = Content::Instance->Get<Texture>("smooth");
	assert(smooth != NULL);

	m_wallFace = new WallFace();
	m_wallFace->Initialize(FaceResolution);
}

bool RevisionTest01::Update(float time, float deltaTime)
{
	this->BaseScene::Update(time, deltaTime);

	Draw();

	return true;
}

void RevisionTest01::Draw()
{	
	m_depthFramebuffer->BindFramebuffer();
	m_depthFramebuffer->AttachColorTexture(m_colorTexture->GetId());

	glDepthMask(true);
	glColorMaski(0, true, true, true, true);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawFace(0.1f);

	DemoController::GetInstance()->m_graphicsEngine->Blur(m_colorTexture, m_interBlurTexture, m_blurTexture);

	m_depthFramebuffer->BindFramebuffer();
	m_depthFramebuffer->AttachColorTexture(m_blurTexture->GetId());
	glDepthMask(true);
	glClear(GL_DEPTH_BUFFER_BIT);

	DrawFace(1.0f, 0.1f);

	Framebuffer::RestoreDefaultFramebuffer();

	glClearColor(0.1f, 0.1f, 0.2f, 0);
	glDepthMask(true);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	DemoController::GetInstance()->m_graphicsEngine->RenderTexture(m_colorTexture->GetId(), 1.0f, 0, 0, FaceResolution, FaceResolution);
	DemoController::GetInstance()->m_graphicsEngine->RenderTexture(m_blurTexture->GetId(), 1.0f, FaceResolution, 0, FaceResolution, FaceResolution);

	glViewport(0, 0, DemoController::GetInstance()->width, DemoController::GetInstance()->height);
	m_wallFace->Draw(m_blurTexture, smooth, DemoController::GetInstance()->m_viewProj);
	//m_wallFace->Draw(m_colorTexture, smooth, DemoController::GetInstance()->m_viewProj);
}

void RevisionTest01::DrawFace(float maxDepthValue, float discardMinDepthValue)
{
	DrawingRoutines::SetViewProjMatrix(
		sm::Matrix::Ortho2DMatrix(-0.7f, 0.7f, -0.7f, 0.7f) *
		sm::Matrix::TranslateMatrix(0, 0, 1));

	//m_mainFrame->BindFramebuffer();
	glViewport(0, 0, FaceResolution, FaceResolution);

	GLenum enabledBuffers[1];
	enabledBuffers[0] = GL_COLOR_ATTACHMENT0;
	//enabledBuffers[1] = GL_COLOR_ATTACHMENT1;
	//	glDrawBuffers(1, enabledBuffers);

	
	//glColorMaski(1, true, true, true, true);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	DrawingRoutines::DrawDepthByZ(m_face->m_meshParts, maxDepthValue, discardMinDepthValue);
}

void RevisionTest01::NotifySynchEvent(SynchEvent* synchEvent)
{
}
