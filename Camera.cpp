#include "Camera.h"
#include "GameObject.h"
#include "FuturisEngine/Screen.h"
#include <GL/glew.h>

Camera::Camera(GameObject* gameObject) :
	Component(gameObject)
{
}

void Camera::SetClearFlag(ClearFlag clearFlag)
{
	m_clearFlag = clearFlag;
}

void Camera::Clear()
{
	unsigned clearFlags = 0;

	if (m_clearFlag == ClearFlag_Depth)
		clearFlags = GL_DEPTH_BUFFER_BIT;
	else if (m_clearFlag == ClearFlag_Color)
		clearFlags = GL_COLOR_BUFFER_BIT;
	else if (m_clearFlag == ClearFlag_ColorAndDepth)
		clearFlags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

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

void Camera::SetProjectionType(ProjectionType projectionType)
{
	m_projectionType = projectionType;
}

const sm::Matrix& Camera::GetViewMatrix()
{
	m_view = m_gameObject->Transform.GetMatrix().GetInversed();

	return m_view;
}

const sm::Matrix& Camera::GetProjMatrix()
{
	if (m_projectionType == ProjectionType_Perspective)
	{
		m_proj = sm::Matrix::PerspectiveMatrix(
			m_horizontalFov,
			(float)m_viewportRect.Width / (float)m_viewportRect.Height,
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

void Camera::Setup()
{
	glViewport(
		(int)((float)Screen::Width * m_viewportRect.X),
		(int)((float)Screen::Height * m_viewportRect.Y),
		(int)((float)Screen::Width * m_viewportRect.Width),
		(int)((float)Screen::Height * m_viewportRect.Height));
}
