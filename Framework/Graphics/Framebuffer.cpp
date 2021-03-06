#include "Framebuffer.h"

#include <Math/MathUtils.h>
#include <GL/glew.h>
#include <assert.h>
#include <stddef.h>

Framebuffer* Framebuffer::Default = new Framebuffer();

Framebuffer::Framebuffer() :
	m_isColorBufferEnabled(true),
	m_isDepthBufferEnabled(true),
	m_clearColor(0, 0, 0, 0),
	m_renderBuffersCount(1)
{
	m_colorBufferType = (Default == NULL) ? GL_BACK : GL_COLOR_ATTACHMENT0;

	framebufferId = 0;
	depthRenderBufferId = 0;
}

Framebuffer::~Framebuffer(void)
{
	if (depthRenderBufferId != 0)
		glDeleteRenderbuffers(1, &depthRenderBufferId);

	if (framebufferId != 0)
		glDeleteFramebuffers(1, &framebufferId);
}

bool Framebuffer::Initialize(int width, int height)
{
	assert(!IsDefault());

	this ->m_width = width;
	this ->m_height = height;

	// depth renderbuffer
	glGenRenderbuffers(1, &depthRenderBufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// framebuffer
	glGenFramebuffers(1, &framebufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void Framebuffer::Setup()
{
	BindFramebuffer();

	if (m_isColorBufferEnabled)
	{
		if (IsDefault())
		{
			glDrawBuffer(GL_BACK);
		}
		else
		{
			GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT };
			glDrawBuffers(m_renderBuffersCount, buffers);
		}
	}
	else
	{
		glDrawBuffer(GL_NONE);
	}
}

void Framebuffer::Validate()
{
	BindFramebuffer();
	unsigned status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	assert(GL_FRAMEBUFFER_COMPLETE == status);

	//#define GL_FRAMEBUFFER_COMPLETE_EXT       0x8CD5
	//#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT 0x8CD6
	//#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT 0x8CD7
	//#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT 0x8CD9
	//#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT 0x8CDA
	//#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT 0x8CDB
	//#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT 0x8CDC
	//#define GL_FRAMEBUFFER_UNSUPPORTED_EXT    0x8CDD
}

void Framebuffer::AttachColorTexture(unsigned textureId, uint32_t index)
{
	assert(!IsDefault());

	m_renderBuffersCount = MathUtils::Max<int>(m_renderBuffersCount, index + 1);

	BindFramebuffer();
	glFramebufferTexture2D(
		GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, textureId, 0);
}

void Framebuffer::AttachDepthTexture(unsigned textureId)
{
	assert(!IsDefault());

	BindFramebuffer();
	glFramebufferTexture2D(
		GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureId, 0);
}

int Framebuffer::GetWidth()
{
	return m_width;
}

int Framebuffer::GetHeight()
{
	return m_height;
}

bool Framebuffer::IsDefault() const
{
	return this == Default;
}

void Framebuffer::BindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
}

void Framebuffer::EnableColorBuffer(bool enable)
{
	m_isColorBufferEnabled = enable;
}

void Framebuffer::EnableDepthBuffer(bool enable)
{
	m_isDepthBufferEnabled = enable;
}

void Framebuffer::SetClearColor(const sm::Vec4& clearColor)
{
	m_clearColor = clearColor;
}

void Framebuffer::Clear(bool color, bool depth)
{
	assert(color || depth);

	uint32_t clearMask = 0;
	if (color && m_isColorBufferEnabled)
	{
		clearMask |= GL_COLOR_BUFFER_BIT;
		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
	}
	if (depth && m_isDepthBufferEnabled)
		clearMask |= GL_DEPTH_BUFFER_BIT;

	if (clearMask != 0)
		glClear(clearMask);
}

