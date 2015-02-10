#pragma once

#include "BaseScene.h"
#include <vector>

class Framebuffer;
class DepthTexture;
class Texture;
class Mesh;
class MeshPart;
class Model;

class RevisionTest01 : public BaseScene
{
public:
	bool Update(float time, float deltaTime);

private:
	void InitializeSubScene();

	void Draw();
	void Initialize();

	void NotifySynchEvent(SynchEvent* synchEvent);

	Framebuffer* m_depthFramebuffer;
	DepthTexture* m_depthTexture;
	Texture* m_colorTexture;

	Model* m_face;
};
