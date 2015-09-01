//#pragma once
//
//#include "Component.h"
//#include "FuturisEngine/LayerId.h"
//#include <Math/Matrix.h>
//#include <Graphics/Rect.h>
//
//class Texture;
//class DepthTexture;
//class Material;
//class Framebuffer;
//
//class PostProcessObserver
//{
//public:
//	virtual void
//};
//
//class PostProcess : public Component
//{
//public:
//
//};

class IPostProcess
{
public:
	virtual void DrawImage() = 0;
};
