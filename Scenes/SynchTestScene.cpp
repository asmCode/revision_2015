#include "SynchTestScene.h"
#include "../GameObject.h"
#include "../GameObjects/BlinkStatic.h"
#include "../Materials/GlowTransparencySpecullar.h"
#include "../SceneLoader.h"
#include <Utils/Random.h>
#include <Graphics/MeshPart.h>
#include <Graphics/Model.h>
#include <Graphics/Shader.h>
#include <Graphics/Content/Content.h>
#include "../SynchEvent.h"
#include <Utils/Log.h>

#include "../Renderable.h"

void SynchTestScene::InitializeSubScene()
{
	SceneLoader sceneLoader;

	if (!sceneLoader.LoadFromFile(this, "SynchTestScene"))
	{
		assert(false);
		return;
	}

	GetGameObjectsOfType<BlinkStatic*>(m_blinks);
}

bool SynchTestScene::Update(float time, float deltaTime)
{
	this->BaseScene::Update(time, deltaTime);

	return true;
}

void SynchTestScene::NotifySynchEvent(SynchEvent* synchEvent)
{
	static Random random;

	sm::Vec4 color(
		(random.GetInt(0, 8) * 32.0f) / 256.0f,
		(random.GetInt(0, 8) * 32.0f) / 256.0f,
		(random.GetInt(0, 8) * 32.0f) / 256.0f,
		1);

	m_blinks[random.GetInt(0, m_blinks.size() - 1)]->Blink(color);

	Log::LogT("%.2f", synchEvent->GetTime());
}
