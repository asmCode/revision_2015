#include "BaseTexture.h"

#include <assert.h>

BaseTexture::BaseTexture(int width, int height) :
	m_width(width),
	m_height(height)
{	
}

BaseTexture::~BaseTexture()
{
	if (m_texId != 0)
		glDeleteTextures(1, &m_texId);
}

void BaseTexture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, m_texId);
}

unsigned BaseTexture::GetId() const
{
	return m_texId;
}

int BaseTexture::GetWidth() const
{
	return m_width;
}

int BaseTexture::GetHeight() const
{
	return m_height;
}

void BaseTexture::SetWrappingMode(BaseTexture::Wrap wrapModel)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModel);
}

void BaseTexture::SetFilterModel(Filter filterMinMode, Filter filterMaxMode)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMinMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMaxMode);
}

void BaseTexture::GenerateMipmaps()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}

