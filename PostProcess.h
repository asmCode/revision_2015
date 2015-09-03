#include "IPostProcess.h"

class Texture;
class Material;
class Framebuffer;
class Quad;

class PostProcess : public IPostProcess
{
public:
	void Init(Texture* mainCameraRT, Texture* mainCameraGlowRT, Texture* backCameraRT);

	void DrawImage();

private:
	Texture* m_mainCameraRT;
	Texture* m_mainCameraGlowRT;
	Texture* m_backCameraRT;
	Quad* m_quad;
	Material* m_blurHoriMaterial;
	Material* m_blurVertMaterial;
	Material* m_blitMaterial;
	Material* m_downsampleX2;
	Material* m_circleDofMaterial;

	Framebuffer* m_blurHoriFramebuffer;

	//Framebuffer* m_;
	Framebuffer* m_blurVertFramebuffer;
	Texture* m_blurHoriTexture;
	Texture* m_blurVertTexture;

	void Draw(Material* material, Framebuffer* framebuffer, bool additive = false);

	void Blur(Texture* texture, int iterations);
};
