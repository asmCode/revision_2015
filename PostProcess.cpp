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

void PostProcess::Init(Texture* backCameraRT)
{
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
	m_downsampleX2->SetParameter("u_texelSize", sm::Vec2(1.0f / (float)backCameraRT->GetWidth(), 1.0f / (float)backCameraRT->GetHeight()));

	Shader* blurHori = Content::Instance->Get<Shader>("BlurHori7");
	m_blurHoriMaterial = new Material();
	m_blurHoriMaterial->SetShader(blurHori);
	//m_blurHoriMaterial->SetParameter("u_tex", backCameraRT);
	m_blurHoriMaterial->SetParameter("u_texelSize", 1.0f / (float)backCameraRT->GetWidth() * 4.6f);

	Shader* blurVert = Content::Instance->Get<Shader>("BlurVert7");
	m_blurVertMaterial = new Material();
	m_blurVertMaterial->SetShader(blurVert);
	//m_blurVertMaterial->SetParameter("u_tex", m_blurTexture);
	m_blurVertMaterial->SetParameter("u_texelSize", 1.0f / (float)backCameraRT->GetHeight() * 4.6f);

	Shader* blit = Content::Instance->Get<Shader>("Blit");
	m_blitMaterial = new Material();
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
	Draw(m_blitMaterial, Framebuffer::Default);

	//m_blitMaterial->SetParameter("u_tex", m_blurVertTexture);
	////m_blitMaterial->SetParameter("u_tex", m_backCameraRT);
	//Draw(m_blitMaterial, Framebuffer::Default);
}

void PostProcess::Draw(Material* material, Framebuffer* framebuffer)
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

	Quad::Setup();
	m_quad->Draw();
	Quad::Clean();
}
