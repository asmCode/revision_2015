#pragma once

#include "Component.h"
#include <Math/Matrix.h>
#include <Graphics/Rect.h>

class Camera : public Component
{
public:
	enum ClearFlag
	{
		ClearFlag_None,
		ClearFlag_Color,
		ClearFlag_Depth,
		ClearFlag_ColorAndDepth,
	};

	enum ProjectionType
	{
		ProjectionType_Perspective,
		ProjectionType_Orthographics
	};

	static const ClearFlag DefaultClearFlag;
	static const ProjectionType DefaultProjectionType;
	static const float DefaultFov;
	static const float DefaultNearPlane;
	static const float DefaultFarPlane;
	static const sm::Rect<float> DefaultViewport;
	static const sm::Vec4 DefaultClearColor;

	Camera(GameObject* gameObject);

	void SetClearFlag(ClearFlag clearFlag);

	void Clear();

	void SetFov(float horizontalFov);
	void SetFarPlane(float farPlane);
	void SetNearPlane(float nearPlane);
	void SetViewport(float x, float y, float width, float height);
	void SetClearColor(const sm::Vec4& clearColor);

	void SetProjectionType(ProjectionType projectionType);

	const sm::Matrix& GetViewMatrix();
	const sm::Matrix& GetProjMatrix();
	const sm::Matrix& GetViewProjMatrix();
	const sm::Vec4& GetClearColor() const;

	void Setup();

private:
	ClearFlag m_clearFlag;
	ProjectionType m_projectionType;

	float m_horizontalFov;
	float m_nearPlane;
	float m_farPlane;
	sm::Rect<float> m_viewportRect;
	sm::Vec4 m_clearColor;

	sm::Matrix m_view;
	sm::Matrix m_proj;
	sm::Matrix m_viewProj;

	float GetAspect() const;
};
