#include "PostProcess.h"
#include "Quad.h"
#include "FuturisEngine/Screen.h"
#include <Graphics/Texture.h>
#include <Graphics/Framebuffer.h>
#include <Graphics/Material.h>
#include <Graphics/Shader.h>
#include <Graphics/Content/Content.h>
#include <Math/Vec2.h>
#include <GL/glew.h>

void PostProcess::Init(Texture* mainCameraRT, Texture* mainCameraGlowRT, Texture* backCameraRT)
{
	m_mainCameraRT = mainCameraRT;
	m_mainCameraGlowRT = mainCameraGlowRT;
	m_backCameraRT = backCameraRT;

	m_quad = new Quad();
	m_quad->Initialize();

	int finalWidth = backCameraRT->GetWidth() / 2;
	int finalHeight = backCameraRT->GetHeight() / 2;

	m_blurHoriTexture = new Texture(
		finalWidth,
		finalHeight,
		32,
		NULL,
		BaseTexture::Wrap_ClampToEdge,
		BaseTexture::Filter_Linear,
		BaseTexture::Filter_Linear,
		false);

	m_blurVertTexture = new Texture(
		finalWidth,
		finalHeight,
		32,
		NULL,
		BaseTexture::Wrap_ClampToEdge,
		BaseTexture::Filter_Linear,
		BaseTexture::Filter_Linear,
		false);

	m_blurHoriFramebuffer = new Framebuffer();
	m_blurHoriFramebuffer->Initialize(finalWidth, finalHeight);
	m_blurHoriFramebuffer->AttachColorTexture(m_blurHoriTexture->GetId());
	m_blurHoriFramebuffer->Validate();

	m_blurVertFramebuffer = new Framebuffer();
	m_blurVertFramebuffer->Initialize(finalWidth, finalHeight);
	m_blurVertFramebuffer->AttachColorTexture(m_blurVertTexture->GetId());
	m_blurVertFramebuffer->Validate();

	Shader* downsampleShader = Content::Instance->Get<Shader>("Downsample");
	m_downsampleX2 = new Material();
	m_downsampleX2->SetShader(downsampleShader);
	m_downsampleX2->SetParameter("u_texelSize",
		sm::Vec2(
		1.0f / (float)backCameraRT->GetWidth() * 8.0f,
		1.0f / (float)backCameraRT->GetHeight() * 8.0f));

	Shader* cornerDofShader = Content::Instance->Get<Shader>("CornerDof");
	m_circleDofMaterial = new Material();
	m_circleDofMaterial->SetOpacity(true);
	m_circleDofMaterial->SetShader(cornerDofShader);
	m_circleDofMaterial->SetParameter("u_circle", sm::Vec2(0.1f, 0.55f));

	Shader* blurHori = Content::Instance->Get<Shader>("BlurHori7");
	m_blurHoriMaterial = new Material();
	m_blurHoriMaterial->SetShader(blurHori);
	//m_blurHoriMaterial->SetParameter("u_tex", backCameraRT);
	m_blurHoriMaterial->SetParameter("u_texelSize", 1.0f / (float)backCameraRT->GetWidth() * 4.8f);

	Shader* blurVert = Content::Instance->Get<Shader>("BlurVert7");
	m_blurVertMaterial = new Material();
	m_blurVertMaterial->SetShader(blurVert);
	//m_blurVertMaterial->SetParameter("u_tex", m_blurTexture);
	m_blurVertMaterial->SetParameter("u_texelSize", 1.0f / (float)backCameraRT->GetHeight() * 4.8f);

	Shader* blit = Content::Instance->Get<Shader>("Blit");
	m_blitMaterial = new Material();
	m_blitMaterial->SetOpacity(true);
	m_blitMaterial->SetShader(blit);
	m_blitMaterial->SetParameter("u_tex", backCameraRT);
}

void PostProcess::DrawImage()
{
	m_downsampleX2->SetParameter("u_tex", m_backCameraRT);
	m_blurVertFramebuffer->AttachColorTexture(m_blurVertTexture->GetId());
	Draw(m_downsampleX2, m_blurVertFramebuffer);

	m_blurHoriMaterial->SetParameter("u_tex", m_blurVertTexture);
	m_blurHoriFramebuffer->AttachColorTexture(m_blurHoriTexture->GetId());
	Draw(m_blurHoriMaterial, m_blurHoriFramebuffer);

	m_blurVertMaterial->SetParameter("u_tex", m_blurHoriTexture);
	m_blurVertFramebuffer->AttachColorTexture(m_blurVertTexture->GetId());
	Draw(m_blurVertMaterial, m_blurVertFramebuffer);

	m_blurHoriMaterial->SetParameter("u_tex", m_blurVertTexture);
	m_blurHoriFramebuffer->AttachColorTexture(m_blurHoriTexture->GetId());
	Draw(m_blurHoriMaterial, m_blurHoriFramebuffer);

	m_blurVertMaterial->SetParameter("u_tex", m_blurHoriTexture);
	m_blurVertFramebuffer->AttachColorTexture(m_blurVertTexture->GetId());
	Draw(m_blurVertMaterial, m_blurVertFramebuffer);

	m_blurHoriMaterial->SetParameter("u_tex", m_blurVertTexture);
	m_blurHoriFramebuffer->AttachColorTexture(m_blurHoriTexture->GetId());
	Draw(m_blurHoriMaterial, m_blurHoriFramebuffer);

	m_blurVertMaterial->SetParameter("u_tex", m_blurHoriTexture);
	m_blurVertFramebuffer->AttachColorTexture(m_blurVertTexture->GetId());
	Draw(m_blurVertMaterial, m_blurVertFramebuffer);

	m_blitMaterial->SetParameter("u_tex", m_blurVertTexture);
	m_blitMaterial->SetOpacity(false);
	Draw(m_blitMaterial, Framebuffer::Default);

	m_blitMaterial->SetParameter("u_tex", m_mainCameraRT);
	m_blitMaterial->SetOpacity(true);
	Draw(m_blitMaterial, Framebuffer::Default);

	Blur(m_mainCameraRT, 3);
	m_circleDofMaterial->SetParameter("u_tex", m_blurVertTexture);
	Draw(m_circleDofMaterial, Framebuffer::Default);

	Blur(m_mainCameraGlowRT, 3);

	m_blitMaterial->SetParameter("u_tex", m_blurVertTexture);
	m_blitMaterial->SetOpacity(true);
	Draw(m_blitMaterial, Framebuffer::Default, true);
	Draw(m_blitMaterial, Framebuffer::Default, true);
	Draw(m_blitMaterial, Framebuffer::Default, true);

	//m_blitMaterial->SetParameter("u_tex", m_blurVertTexture);
	////m_blitMaterial->SetParameter("u_tex", m_backCameraRT);
	//Draw(m_blitMaterial, Framebuffer::Default);
}

void PostProcess::Blur(Texture* texture, int iterations)
{
	m_downsampleX2->SetParameter("u_tex", texture);
	m_blurVertFramebuffer->AttachColorTexture(m_blurVertTexture->GetId());
	Draw(m_downsampleX2, m_blurVertFramebuffer);

	m_blurHoriMaterial->SetParameter("u_tex", m_blurVertTexture);
	m_blurHoriFramebuffer->AttachColorTexture(m_blurHoriTexture->GetId());
	Draw(m_blurHoriMaterial, m_blurHoriFramebuffer);

	m_blurVertMaterial->SetParameter("u_tex", m_blurHoriTexture);
	m_blurVertFramebuffer->AttachColorTexture(m_blurVertTexture->GetId());
	Draw(m_blurVertMaterial, m_blurVertFramebuffer);

	m_blurHoriMaterial->SetParameter("u_tex", m_blurVertTexture);
	m_blurHoriFramebuffer->AttachColorTexture(m_blurHoriTexture->GetId());
	Draw(m_blurHoriMaterial, m_blurHoriFramebuffer);

	m_blurVertMaterial->SetParameter("u_tex", m_blurHoriTexture);
	m_blurVertFramebuffer->AttachColorTexture(m_blurVertTexture->GetId());
	Draw(m_blurVertMaterial, m_blurVertFramebuffer);

	m_blurHoriMaterial->SetParameter("u_tex", m_blurVertTexture);
	m_blurHoriFramebuffer->AttachColorTexture(m_blurHoriTexture->GetId());
	Draw(m_blurHoriMaterial, m_blurHoriFramebuffer);

	m_blurVertMaterial->SetParameter("u_tex", m_blurHoriTexture);
	m_blurVertFramebuffer->AttachColorTexture(m_blurVertTexture->GetId());
	Draw(m_blurVertMaterial, m_blurVertFramebuffer);
}

void PostProcess::Draw(Material* material, Framebuffer* framebuffer, bool additive)
{
	int width = framebuffer == Framebuffer::Default ? Screen::Width : framebuffer->GetWidth();
	int height = framebuffer == Framebuffer::Default ? Screen::Height : framebuffer->GetHeight();

	framebuffer->Setup();
	glViewport(0, 0, width, height);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDepthMask(false);
	glColorMask(true, true, true, true);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	material->SetupMaterial();

	if (additive)
		glBlendFunc(GL_ONE, GL_ONE);

	Quad::Setup();
	m_quad->Draw();
	Quad::Clean();
}
