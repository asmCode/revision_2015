#include "PlaneObject.h"
#include "../GameObject.h"
#include "../Renderable.h"
#include "../FuturisEngine/Graphics/Mesh.h"
#include <UserInput/Input.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>
#include <Graphics/Material.h>
#include <Graphics/Content/Content.h>

using namespace FuturisEngine::Graphics;

PlaneObject* PlaneObject::Create(const std::string& spriteName)
{
	Texture* sprite = Content::Instance->Get<Texture>(spriteName);
	sprite->BindTexture();
	sprite->SetWrappingMode(BaseTexture::Wrap_ClampToEdge);
	Shader* solidShader = Content::Instance->Get<Shader>("Sprite3d");
	Material* material = new Material();
	material->SetOpacity(true);
	material->SetShader(solidShader);
	material->SetParameter("u_color", sm::Vec4(1, 1, 1, 1.0f));
	material->SetParameter("u_tex", sprite);

	float proportion = (float)sprite->GetHeight() / (float)sprite->GetWidth();

	sm::Vec3 vertices[4] = 
	{
		sm::Vec3(0, 0, 0),
		sm::Vec3(1, 0, 0),
		sm::Vec3(1, proportion, 0),
		sm::Vec3(0, proportion, 0),
	};

	uint32_t indices[6] =
	{
		0, 1, 2,
		0, 2, 3
	};

	sm::Vec2 coords[4] =
	{
		sm::Vec2(0, 0),
		sm::Vec2(1, 0),
		sm::Vec2(1, 1),
		sm::Vec2(0, 1),
	};

	Mesh* mesh = new Mesh();
	mesh->SetVertices(vertices, 4);
	mesh->SetCoords1(coords, 4);
	mesh->SetIndices(indices, 6);
	mesh->Apply();

	GameObject* go = new GameObject("PlaneObject");
	PlaneObject* planeObject = dynamic_cast<PlaneObject*>(go->AddComponent("PlaneObject"));

	Renderable* renderable = new Renderable(go, mesh, material);
	go->AddRenderable(renderable);

	return planeObject;
}

PlaneObject::PlaneObject(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}


void PlaneObject::SetSpriteColor(const sm::Vec4& color)
{
	GetGameObject()->GetRenderables()[0]->GetMaterial()->SetParameter("u_color", color);
}

sm::Vec4 PlaneObject::GetSpriteColor() const
{
	return GetGameObject()->GetRenderables()[0]->GetMaterial()->GetParameterVec4("u_color");
}
