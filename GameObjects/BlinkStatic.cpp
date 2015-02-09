#include "BlinkStatic.h"
#include "../Renderable.h"
#include "../Materials/BaseGlowTransparencySpecullar.h"
#include <Math/MathUtils.h>
#include <Animation/QuadOut.h>
#include <Animation/QuadIn.h>

BlinkStatic::BlinkStatic(const std::string& sceneName, SceneElement::CustomSceneElement* data) :
	m_duration(1.0f),
	m_time(0.0f),
	m_isBlinking(false)
{
	SceneElement::StaticData* staticData = new SceneElement::StaticData();
	staticData->Material = data->Material;
	staticData->MeshName = data->MeshName;
	staticData->Order = 0;

	m_static = new Static(sceneName, staticData);

	m_baseColor = ((BaseGlowTransparencySpecullar*)m_static->GetRenderables()[0]->GetMaterial())->GetColor();

	// bardzo brzydkie rozwiazanie - kopiowanie renerables z obiektu Static
	m_renderables.insert(m_renderables.begin(), m_static->GetRenderables().begin(), m_static->GetRenderables().end());
}

void BlinkStatic::Update(float time, float deltaTime)
{
	if (!m_isBlinking)
		return;

	m_time += deltaTime;
	m_time = MathUtils::Min(m_time, m_duration);

	static QuadIn<sm::Vec4> curve;

	BaseGlowTransparencySpecullar* material = (BaseGlowTransparencySpecullar*)m_static->GetRenderables()[0]->GetMaterial();
	material->SetColor(curve.Evaluate(m_blinkColor, m_baseColor, m_time / m_duration));

	if (m_time >= m_duration)
		m_isBlinking = false;
}

void BlinkStatic::Blink(const sm::Vec4& color)
{
	m_isBlinking = true;
	m_time = 0.0f;
	m_blinkColor = color;
	m_blinkColor.w = m_baseColor.w;
}
