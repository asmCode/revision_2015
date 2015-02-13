#include "WallFace.h"

#include "PlaneMesh.h"
#include <Math/Matrix.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>
#include <Graphics/Content/Content.h>

#include <stddef.h>
#include <assert.h>

WallFace::WallFace() :
	m_planeMesh(NULL),
	m_wallFaceShader(NULL)
{

}

WallFace::~WallFace()
{
	if (m_planeMesh != NULL)
		delete m_planeMesh;
}

void WallFace::Initialize(int resolution)
{
	m_planeMesh = new PlaneMesh();
	m_planeMesh->Initialize(resolution, resolution);

	m_wallFaceShader = Content::Instance->Get<Shader>("WallFace");
	assert(m_wallFaceShader != NULL);
}

void WallFace::Update(float time, float deltaTime)
{

}

void WallFace::SetMvpMatrix(const sm::Matrix& mvp)
{
}

void WallFace::Draw(Texture* depth, Texture* smooth, const sm::Matrix& mvp)
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthMask(true);
	glColorMask(true, true, true, true);

	m_wallFaceShader->UseProgram();

	m_wallFaceShader->SetTextureParameter("u_depthTex", 0, depth->GetId());
	m_wallFaceShader->SetTextureParameter("u_smoothTex", 1, smooth->GetId());
	m_wallFaceShader->SetMatrixParameter("u_mvp", mvp);

	m_planeMesh->Setup();
	m_planeMesh->Draw();
	m_planeMesh->Clean();
}

void WallFace::SetupGraphicsState()
{

}
