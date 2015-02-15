#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

class BaseTexture
{
public:
	enum Wrap
	{
		Wrap_Repeat					= GL_REPEAT,
		Wrap_ClampToEdge			= GL_CLAMP_TO_EDGE
	};

	enum Filter
	{
		Filter_Nearest				= GL_NEAREST,
		Filter_Linear				= GL_LINEAR,
		Filter_LinearMipmapLinear	= GL_LINEAR_MIPMAP_LINEAR
	};

	BaseTexture(int width, int height);

	virtual ~BaseTexture();

	int GetWidth() const;
	int GetHeight() const;

	void BindTexture();
	unsigned GetId() const;

	// Bind texture before this method
	void SetWrappingMode(Wrap wrapModel);

	// Bind texture before this method
	void SetFilterModel(Filter filterMinMode, Filter filterMaxMode);

	// Bind texture before this method
	void GenerateMipmaps();

protected:
	unsigned m_texId;

	int m_width;
	int m_height;
};
