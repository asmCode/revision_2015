#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "FuturisEngine/Screen.h"
#include "FuturisEngine/PropertyContainer.h"
#include <Graphics/Framebuffer.h>
#include <Graphics/Texture.h>
#include <Graphics/DepthTexture.h>
#include <Math/MathUtils.h>
#include <GL/glew.h>

const std::string Camera::CameraComponentName = "Camera";

const Camera::ClearFlag Camera::DefaultClearFlag = Camera::ClearFlag_ColorAndDepth;
const Camera::ProjectionType Camera::DefaultProjectionType = Camera::ProjectionType_Perspective;
const float Camera::DefaultFov = 3.1415f / 3.0f; // 60 degrees
const float Camera::DefaultOrthoSize = 100.0f;
const float Camera::DefaultNearPlane = 1.0f;
const float Camera::DefaultFarPlane = 100.0f;
const sm::Rect<float> Camera::DefaultViewport = sm::Rect<float>(0, 0, 1, 1);
const sm::Vec4 Camera::DefaultClearColor = sm::Vec4(0.2f, 0.1f, 0.1f, 0.0f);

Camera::Camera(GameObject* gameObject) :
	Component(CameraComponentName, gameObject),
	m_clearFlag(DefaultClearFlag),
	m_projectionType(DefaultProjectionType),
	m_cullLayers(LayerId_All),
	m_horizontalFov(DefaultFov),
	m_orthoSize(DefaultOrthoSize),
	m_nearPlane(DefaultNearPlane),
	m_farPlane(DefaultFarPlane),
	m_viewportRect(DefaultViewport),
	m_clearColor(DefaultClearColor),
	m_depth(0),
	m_framebuffer(Framebuffer::Default),
	m_replacementMaterial(NULL)
{
	GetPropertyContainer()->AddProperty<Camera, float>("fov", PropertyType_Float, this, &Camera::SetFov, &Camera::GetFov);
}

void Camera::SetClearFlag(ClearFlag clearFlag)
{
	m_clearFlag = clearFlag;
}

void Camera::SetCullLayers(Layers cullLayers)
{
	m_cullLayers = cullLayers;
}

void Camera::Clear()
{
	m_framebuffer->SetClearColor(m_clearColor);
	m_framebuffer->Clear(
		m_clearFlag == ClearFlag_Color || m_clearFlag == ClearFlag_ColorAndDepth,
		m_clearFlag == ClearFlag_Depth || m_clearFlag == ClearFlag_ColorAndDepth);
}

void Camera::SetFov(const float& horizontalFov)
{
	m_horizontalFov = horizontalFov;
}

float Camera::GetFov() const
{
	return m_horizontalFov;
}

void Camera::SetFarPlane(float farPlane)
{
	m_farPlane = farPlane;
}

void Camera::SetNearPlane(float nearPlane)
{
	m_nearPlane = nearPlane;
}

void Camera::SetViewport(float x, float y, float width, float height)
{
	m_viewportRect.X = x;
	m_viewportRect.Y = y;
	m_viewportRect.Width = width;
	m_viewportRect.Height = height;
}

void Camera::SetClearColor(const sm::Vec4& clearColor)
{
	m_clearColor = clearColor;
}

void Camera::SetDepth(int depth)
{
	m_depth = depth;
}

void Camera::SetOrthoSize(float orthoSize)
{
	m_orthoSize = orthoSize;
}

void Camera::SetProjectionType(ProjectionType projectionType)
{
	m_projectionType = projectionType;
}

const sm::Matrix& Camera::GetViewMatrix()
{
	m_view = m_gameObject->GetTransform().GetMatrix().GetInversed(); // TODO: optymalizacja!!

	return m_view;
}

const sm::Matrix& Camera::GetProjMatrix()
{
	if (m_projectionType == ProjectionType_Perspective)
	{
		m_proj = sm::Matrix::PerspectiveMatrix(
			m_horizontalFov,
			GetAspect(),
			m_nearPlane,
			m_farPlane);
	}
	else
	{
		float aspect = GetAspect();

		m_proj = sm::Matrix::Ortho2DMatrix(
			-m_orthoSize,
			m_orthoSize,
			-m_orthoSize / aspect,
			m_orthoSize / aspect);
	}

	return m_proj;
}

const sm::Matrix& Camera::GetViewProjMatrix()
{
	m_viewProj = m_proj * m_view;

	return m_viewProj;
}

const sm::Vec4& Camera::GetClearColor() const
{
	return m_clearColor;
}

int Camera::GetDepth() const
{
	return m_depth;
}

Layers Camera::GetCullLayers() const
{
	return m_cullLayers;
}

void Camera::EnableColorBuffer(bool enable)
{
	m_framebuffer->EnableColorBuffer(enable);
}

void Camera::EnableDepthBuffer(bool enable)
{
	m_framebuffer->EnableDepthBuffer(enable);
}

void Camera::SetRenderToTexture(Texture* texture, DepthTexture* depthTexture)
{
	// disable offscreen
	if (texture == NULL && depthTexture == NULL && !m_framebuffer->IsDefault())
	{
		delete m_framebuffer;
		m_framebuffer = Framebuffer::Default;
	}
	// enable offscreen
	else if (texture != NULL || depthTexture != NULL)
	{
		if (!m_framebuffer->IsDefault())
			delete m_framebuffer;

		int width = texture != NULL ? texture->GetWidth() : depthTexture->GetWidth();
		int height = texture != NULL ? texture->GetHeight() : depthTexture->GetHeight();

		m_framebuffer = new Framebuffer();
		m_framebuffer->Initialize(width, height);

		if (texture != NULL)
			m_framebuffer->AttachColorTexture(texture->GetId());

		if (depthTexture != NULL)
			m_framebuffer->AttachDepthTexture(depthTexture->GetId());

		m_framebuffer->Validate();
	}
}

void Camera::Setup()
{
	int width = GetTargetWidth();
	int height = GetTargetHeight();

	glViewport(
		(int)((float)width * m_viewportRect.X),
		(int)((float)height * m_viewportRect.Y),
		(int)((float)width * m_viewportRect.Width),
		(int)((float)height * m_viewportRect.Height));

	glScissor(
		(int)((float)width * m_viewportRect.X),
		(int)((float)height * m_viewportRect.Y),
		(int)((float)width * m_viewportRect.Width),
		(int)((float)height * m_viewportRect.Height));


	m_framebuffer->Setup();
}

int Camera::GetTargetWidth() const
{
	if (!m_framebuffer->IsDefault())
		return m_framebuffer->GetWidth();
	else
		return Screen::Width;
}

int Camera::GetTargetHeight() const
{
	if (!m_framebuffer->IsDefault())
		return m_framebuffer->GetHeight();
	else
		return Screen::Height;
}

float Camera::GetAspect() const
{
	return
		((float)GetTargetWidth() * m_viewportRect.Width) /
		((float)GetTargetHeight() * m_viewportRect.Height);
}

void Camera::SetReplacementMaterial(Material* material)
{
	m_replacementMaterial = material;
}

Material* Camera::GetReplacementMaterial() const
{
	return m_replacementMaterial;
}

