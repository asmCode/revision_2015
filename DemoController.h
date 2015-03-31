#pragma once

#include "DemoOptions.h"
#include "GraphicsLibrary\CubeTexture.h"

#include <Core/GenericSingleton.h>

#include <Graphics/Content/Content.h>

#include <Graphics/Interpolators/InterpolatorFactory.h>
#include <Graphics/IGraphicsEngine.h>
#include "GraphicsLibrary/AnimCamera.h"
#include <Graphics/AnimationData.h>

#include "GraphicsLibrary\OpenglWindow.h"

#include "Particles/ParticleEmmiter.h"

#include "AnimCameraManager.h"
#include <Graphics/Interpolators/Interpolator.h>
#include <Graphics/Interpolators/InterpolatorFactory.h>
#include <Graphics/Content/IContentObserver.h>
#include <Utils/Random.h>

#include <windows.h>
#include <vector>
#include <map>

class BaseScene;
class ScenesManager;
class SynchManager;

class LoadingScreen;
class ParticlesManager;
class Framebuffer;
class DepthTexture;
class Blur;
class Frustum;
class Screens;
class PropertySignal;
class Content;
class SpriteBatch;
class FontRenderer;
class DistortParticleHandler;
class GameObject;
class GraphicsEngine;
class Engine;

#define demo DemoController::GetInstance()

class DemoController :
	public IContentObserver,
	public IGraphicsEngine,
	public GenericSingleton<DemoController>
{
	friend class GenericSingleton<DemoController>;
	friend class LoadingScreen;

public:
	static const float GlowBufferWidthRatio;
	static const float GlowBufferHeightRatio;

	Engine* m_engine;

	float tmp_progress;

	Content *m_content;

	enum GeometryBatches
	{
		GeometryBatches_FactoryHall = 0,
		GeometryBatches_Passage,
		GeometryBatches_RobotLying,
		GeometryBatches_RobotMoving,
		GeometryBatches_MechArms,
		GeometryBatches_Count
	};

	std::string m_strBasePath;

	PropertySignal *m_fovSignal;

	float m_fovPower;

	Texture *m_bgTex;
	Shader *m_distortShader;

	ICamera *m_activeCamera;
	SynchManager* m_synchManager;

	/*ParticleEmmiter *m_particleEmmiter;
	DistortParticleHandler *m_distortParticleHandler;*/

	//Texture *m_particleTex;
	//Texture *m_distortParticleTex;

	SpriteBatch *m_spriteBatch;
	FontRenderer *m_fontRenderer;
	Shader *m_spriteShader;
	
	//Effect *electro;

	unsigned noiseTex;
	void InitElectroNoise();

	IInterpolator<float> *eyeBlinkAnim;
	IInterpolator<float> *eyeRangeAnim;

	float eyeBlinkVal;
	float eyeRangeVal;
	float electroNoiseVal;
	float camShakeVal;

	AnimCameraManager animCamsMng;
	AnimCameraManager m_lightCamsMng;
	ICamera *currentCamera;
	ICamera *m_currentLightCamera;

	float fade;

	float CalcFlash(float time, float ms);

	bool isPlaying;

	Texture *mask;

	bool errorOccured;

	OpenglWindow *glWnd;

	float m_biasScale;
	float m_biasClamp;

	Animation *camerasAnimation;
	Animation *camerasFactoryAnimation;

	Frustum *frustum;
	bool isStereo;

	ParticlesManager *m_particlesManager;

	Framebuffer *blurFbo;
	Texture *targetTex0;

	float m_greetzDanceTime;

	bool firstupdate;

	float m_endScreenOpacity;

	DepthTexture *m_shadowMapTexture;
	Texture *m_dummyColorTexture;
	Framebuffer *m_shadowMappingFramebuffer;

	Blur *blur;
	Blur *dofBlur;

	Texture *m_mainFrameTexture;

	Framebuffer *m_distortionFramebuffer;
	Texture *m_distortionTexture;

	LoadingScreen *loadingScreen;

	GraphicsEngine* m_graphicsEngine;

	DemoController();
	~DemoController();

	void SetOpenglParams();
	bool InitCg();

	// IContentObserver interface
	void ErrorOccured(const std::string &errorMsg);
	void OnLoadingContentStarted(int stepsCount);
	void OnProgressStep();
	void OnLoadingFinished();

	template <typename T>
	void DeleteObject(T &obj)
	{
		if (obj != NULL)
		{
			delete obj;
			obj = NULL;
		}
	}

	void DrawText(const std::string &text, int x, int y, BYTE r = 255, BYTE g = 255, BYTE b = 255);
	float CalcFps(float ms);

	int width;
	int height;

	int flaps;
	float delay;
	float delayLimit;
	float fps;

	void DrawGlowTexture();
	void DrawShadowMap();

public:
	void AssignLightmapsToModels();

	void InitializeBlur();

	bool Initialize(bool isStereo, HWND parent, const char *title, int width, int height,
		int bpp, int freq, bool fullscreen, bool createOwnWindow);
	bool LoadContent(const char *basePath);
	bool BeforeStartSetups();
	void Release();

	bool Update(float time, float ms);
	bool Draw(float time, float ms);

	void LoadProperties(const std::string &filename);


	void DrawPostProcess(int sharpTexId, int blurTexId, int glowTex, unsigned int shadowTex, float fade);

	Texture* LoadTexture(const std::string &path);
	Shader* LoadShader(const std::string &vertexShaderPath,
										const std::string &fragmentShaderPath);
	Model* LoadModel(const std::string &path);
	AnimationData* LoadAnimation(const std::string &path);
	Material* LoadMaterial(const std::string &path);

	AnimationCurve<float> m_endScreenAnim;
	AnimationCurve<float> m_startScreenAnim;
	AnimCamera* m_prevCamera;
	float nextFadeTime;
	Texture* m_fadeTex;
	Texture* m_endScreen;
	Texture* m_startScreen;
	Texture* m_mask;

	void RegisterBehaviours();
};
