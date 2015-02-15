#pragma once

#include "BaseScene.h"
#include <vector>

class Framebuffer;
class Texture;
class Mesh;
class MeshPart;
class Model;
class WallFace;
class DepthTexture;

class RevisionTest01 : public BaseScene
{
public:
	bool Update(float time, float deltaTime);

private:
	static const int FaceResolution = 128;

	void InitializeSubScene();

	void Draw();
	void Initialize();

	void NotifySynchEvent(SynchEvent* synchEvent);

	void DrawFace(float maxDepthValue, float discardMinDepthValue = 0.0f);

	Framebuffer* m_depthFramebuffer;
	Texture* m_colorTexture;
	Texture* m_interBlurTexture;
	Texture* m_blurTexture;

	Model* m_face;
	WallFace* m_wallFace;
};
