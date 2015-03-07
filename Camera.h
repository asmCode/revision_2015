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

	Camera(GameObject* gameObject);

	void SetClearFlag(ClearFlag clearFlag);

	void Clear();

	void SetFov(float horizontalFov);
	void SetFarPlane(float farPlane);
	void SetNearPlane(float nearPlane);
	void SetViewport(float x, float y, float width, float height);

	void SetProjectionType(ProjectionType projectionType);

	const sm::Matrix& GetViewMatrix();
	const sm::Matrix& GetProjMatrix();
	const sm::Matrix& GetViewProjMatrix();

	void Setup();

private:
	static const ClearFlag DefaultClearFlag;
	static const ProjectionType DefaultProjectionType;
	static const float DefaultFov;
	static const float DefaultNearPlane;
	static const float DefaultFarPlane;

	ClearFlag m_clearFlag;
	ProjectionType m_projectionType;

	float m_horizontalFov;
	float m_nearPlane;
	float m_farPlane;
	sm::Rect<float> m_viewportRect;

	sm::Matrix m_view;
	sm::Matrix m_proj;
	sm::Matrix m_viewProj;
};
