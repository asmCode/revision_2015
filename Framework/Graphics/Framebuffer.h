#pragma once

#include <Math/Vec4.h>
#include <stdint.h>

// TODO: optymalizacja. Mozna w statycznych polach przechowywac aktualny stan
// bindowania itp i uniknac niepotrzebnych zmian stanow per framebufer

class Framebuffer
{
public:
	static Framebuffer* Default;

	Framebuffer();
	~Framebuffer(void);

	bool Initialize(int width, int height);

	void Setup();
	void Validate();

	void AttachColorTexture(unsigned textureId, uint32_t index = 0);
	void AttachDepthTexture(unsigned textureId);

	void EnableColorBuffer(bool enable);
	void EnableDepthBuffer(bool enable);

	void SetClearColor(const sm::Vec4& clearColor);
	void Clear(bool color = true, bool depth = true);

	int GetWidth();
	int GetHeight();

	bool IsDefault() const;

private:
	unsigned m_colorBufferType;
	unsigned framebufferId;
	unsigned depthRenderBufferId;

	int m_width;
	int m_height;

	bool m_isColorBufferEnabled;
	bool m_isDepthBufferEnabled;
	sm::Vec4 m_clearColor;

	void BindFramebuffer();
};

