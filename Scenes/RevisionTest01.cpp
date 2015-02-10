#include "RevisionTest01.h"
#include "../GameObject.h"
#include "../Materials/GlowTransparencySpecullar.h"
#include "../SceneLoader.h"
#include <Utils/Randomizer.h>
#include <Graphics/MeshPart.h>
#include <Graphics/Model.h>
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
	m_depthTexture = new DepthTexture(128, 128);

	m_colorTexture = new Texture(
		128,
		128,
		32,
		NULL,
		Texture::Wrap_ClampToEdge,
		Texture::Filter_Linear,
		Texture::Filter_Linear,
		false);

	m_depthFramebuffer = new Framebuffer();
	m_depthFramebuffer->Initialize(128, 128, 32);
	m_depthFramebuffer->BindFramebuffer();
	m_depthFramebuffer->AttachColorTexture(m_colorTexture->GetId());
	m_depthFramebuffer->AttachDepthTexture(m_depthTexture->GetId());
	m_depthFramebuffer->Validate();

	m_face = Content::Instance->Get<Model>("face");
	assert(m_face != NULL);
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

	DrawingRoutines::SetViewProjMatrix(
		sm::Matrix::PerspectiveMatrix(MathUtils::Deg2Rad * 60.0f, 1.0f, 0.1f, 10.0f) *
		DemoController::GetInstance()->m_view);

	//m_mainFrame->BindFramebuffer();
	glViewport(0, 0, 128, 128);

	GLenum enabledBuffers[1];
	enabledBuffers[0] = GL_COLOR_ATTACHMENT0;
	//enabledBuffers[1] = GL_COLOR_ATTACHMENT1;
//	glDrawBuffers(1, enabledBuffers);

	glDepthMask(true);
	glColorMaski(0, true, true, true, true);
	//glColorMaski(1, true, true, true, true);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	DrawingRoutines::DrawBlack(m_face->m_meshParts);

	Framebuffer::RestoreDefaultFramebuffer();

	DemoController::GetInstance()->m_graphicsEngine->RenderTexture(m_colorTexture->GetId(), 1.0f, 0, 0, 128, 128);
	DemoController::GetInstance()->m_graphicsEngine->RenderTexture(m_depthTexture->GetId(), 1.0f, 128, 0, 128, 128);
}

void RevisionTest01::NotifySynchEvent(SynchEvent* synchEvent)
{
}
