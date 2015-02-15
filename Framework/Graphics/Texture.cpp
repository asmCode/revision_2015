#include "Texture.h"

#include <assert.h>

Texture::Texture() : BaseTexture(0, 0)
{
	this ->bpp = 0;
	this ->m_texId = 0;	
}

Texture::Texture(
	int width,
	int height,
	int bpp,
	const void *data,
	Wrap wrap,
	Filter minFilter,
	Filter magFilter,
	bool genMipmaps) : BaseTexture(width, height)
{	
	this ->bpp = bpp;
	this ->m_texId = 0;
	
	GLenum format = 0;
	switch (bpp)
	{
		case 32: format = GL_RGBA; break;
		case 24: format = GL_RGB; break;
		case 16: assert(0); break;
		case 8: format = GL_ALPHA; break;
	}
	
	glGenTextures(1, &m_texId);
	glBindTexture(GL_TEXTURE_2D, m_texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	if (genMipmaps)
		glGenerateMipmap(GL_TEXTURE_2D);
}


Texture::Texture(
	int width,
	int height,
	int bpp,
	const void *data,
	Wrap wrap,
	Filter minFilter,
	Filter magFilter,
	bool genMipmaps,
	bool c) : BaseTexture(width, height)
{
	this->bpp = bpp;
	this->m_texId = 0;

	GLenum format = 0;
	switch (bpp)
	{
	case 32: format = GL_RGBA; break;
	case 24: format = GL_RGB; break;
	case 16: assert(0); break;
	case 8: format = GL_ALPHA; break;
	}

	glGenTextures(1, &m_texId);
	glBindTexture(GL_TEXTURE_2D, m_texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R16F, width, height, 0, GL_RGBA, GL_FLOAT, data);

	if (genMipmaps)
		glGenerateMipmap(GL_TEXTURE_2D);
}

int Texture::GetBpp() const
{
	return bpp;
}

void Texture::SetTextureData(const void *data)
{
	SetTextureData(0, 0, m_width, m_height, bpp, data);
}

void Texture::SetTextureData(int x, int y, int width, int height, int bpp, const void *data)
{
	BindTexture();
	
	GLenum format = 0;
	switch (bpp)
	{
		case 32: format = GL_RGBA; break;
		case 24: format = GL_RGB; break;
		case 16: assert(0); break;
		case 8: format = GL_ALPHA; break;
	}
	
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, format, GL_UNSIGNED_BYTE, data);
}
