#pragma once

#include "Component.h"
#include "FuturisEngine/LayerId.h"
#include <Math/Matrix.h>
#include <Graphics/Rect.h>

class Texture;
class Framebuffer;

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
	static const float DefaultOrthoSize;
	static const float DefaultNearPlane;
	static const float DefaultFarPlane;
	static const sm::Rect<float> DefaultViewport;
	static const sm::Vec4 DefaultClearColor;

	Camera(GameObject* gameObject);

	void SetClearFlag(ClearFlag clearFlag);
	void SetCullLayers(Layers m_cullLayers);

	void Clear();

	void SetFov(float horizontalFov);
	void SetFarPlane(float farPlane);
	void SetNearPlane(float nearPlane);
	void SetViewport(float x, float y, float width, float height);
	void SetClearColor(const sm::Vec4& clearColor);
	void SetDepth(int depth);

	void SetProjectionType(ProjectionType projectionType);

	const sm::Matrix& GetViewMatrix();
	const sm::Matrix& GetProjMatrix();
	const sm::Matrix& GetViewProjMatrix();
	const sm::Vec4& GetClearColor() const;
	int GetDepth() const;
	Layers GetCullLayers() const;

	void SetRenderToTexture(Texture* texture);

	void Setup();

	bool HasRenderTexture() const;

private:
	ClearFlag m_clearFlag;
	ProjectionType m_projectionType;
	Layers m_cullLayers;

	float m_horizontalFov;
	float m_orthoSize;
	float m_nearPlane;
	float m_farPlane;
	sm::Rect<float> m_viewportRect;
	sm::Vec4 m_clearColor;
	int m_depth;

	sm::Matrix m_view;
	sm::Matrix m_proj;
	sm::Matrix m_viewProj;

	Texture* m_renderTexture;
	Framebuffer* m_framebuffer;

	int GetTargetWidth() const;
	int GetTargetHeight() const;
	float GetAspect() const;
};
