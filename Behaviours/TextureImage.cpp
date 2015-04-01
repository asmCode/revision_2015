#include "TextureImage.h"
#include "../GameObject.h"

TextureImage::TextureImage(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
	RegisterParameter("layer", &m_layer);
	RegisterParameter("texture", &m_textureName);
	RegisterParameter("bounds", &m_bounds);
}

void TextureImage::Awake()
{
}

void TextureImage::Update()
{
}
