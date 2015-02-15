#pragma once

#include "BaseTexture.h"
#include <GL/glew.h>
#include <GL/GL.h>

class Texture : public BaseTexture
{
protected:
	int bpp;

public:
	Texture();
	Texture(
		int width,
		int height,
		int bpp,
		const void *data,
		Wrap wrap,
		Filter minFilter,
		Filter magFilter,
		bool genMipmaps);

	Texture(
		int width,
		int height,
		int bpp,
		const void *data,
		Wrap wrap,
		Filter minFilter,
		Filter magFilter,
		bool genMipmaps,
		bool c);

	int GetBpp() const;
	
	void SetTextureData(const void *data);	
	void SetTextureData(int x, int y, int width, int height, int bpp, const void *data);
};
