#include "Camera.h"
#include "GameObject.h"
#include "FuturisEngine/Screen.h"
#include <Math/MathUtils.h>
#include <GL/glew.h>

const Camera::ClearFlag Camera::DefaultClearFlag = Camera::ClearFlag_ColorAndDepth;
const Camera::ProjectionType Camera::DefaultProjectionType = Camera::ProjectionType_Perspective;
const float Camera::DefaultFov = 3.1415f / 3.0f; // 60 degrees
const float Camera::DefaultNearPlane = 1.0f;
const float Camera::DefaultFarPlane = 1000.0f;
const sm::Rect<float> Camera::DefaultViewport = sm::Rect<float>(0, 0, 1, 1);
const sm::Vec4 Camera::DefaultClearColor = sm::Vec4(0.2f, 0.1f, 0.1f, 0.0f);

Camera::Camera(GameObject* gameObject) :
	Component(gameObject),
	m_clearFlag(DefaultClearFlag),
	m_projectionType(DefaultProjectionType),
	m_cullLayers(LayerId_All),
	m_horizontalFov(DefaultFov),
	m_nearPlane(DefaultNearPlane),
	m_farPlane(DefaultFarPlane),
	m_viewportRect(DefaultViewport),
	m_clearColor(DefaultClearColor)
{
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
	unsigned clearFlags = 0;

	if (m_clearFlag == ClearFlag_Depth)
		clearFlags = GL_DEPTH_BUFFER_BIT;
	else if (m_clearFlag == ClearFlag_Color)
	{
		clearFlags = GL_COLOR_BUFFER_BIT;
		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
	}
	else if (m_clearFlag == ClearFlag_ColorAndDepth)
	{
		clearFlags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
	}

	if (clearFlags != 0)
		glClear(clearFlags);
}

void Camera::SetFov(float horizontalFov)
{
	m_horizontalFov = horizontalFov;
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

void Camera::SetProjectionType(ProjectionType projectionType)
{
	m_projectionType = projectionType;
}

const sm::Matrix& Camera::GetViewMatrix()
{
	m_view = m_gameObject->Transform.GetMatrix().GetInversed(); // TODO: optymalizacja!!

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
		m_proj = sm::Matrix::Ortho2DMatrix(
			m_viewportRect.X,
			m_viewportRect.X + m_viewportRect.Width,
			m_viewportRect.Y,
			m_viewportRect.Y + m_viewportRect.Height);
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

Layers Camera::GetCullLayers() const
{
	return m_cullLayers;
}

void Camera::Setup()
{
	glViewport(
		(int)((float)Screen::Width * m_viewportRect.X),
		(int)((float)Screen::Height * m_viewportRect.Y),
		(int)((float)Screen::Width * m_viewportRect.Width),
		(int)((float)Screen::Height * m_viewportRect.Height));

	glScissor(
		(int)((float)Screen::Width * m_viewportRect.X),
		(int)((float)Screen::Height * m_viewportRect.Y),
		(int)((float)Screen::Width * m_viewportRect.Width),
		(int)((float)Screen::Height * m_viewportRect.Height));
}

float Camera::GetAspect() const
{
	return
		((float)Screen::Width * m_viewportRect.Width) /
		((float)Screen::Height * m_viewportRect.Height);
}
