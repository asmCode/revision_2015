#pragma once

#include "../Behaviour.h"
#include <string>

class GameObject;
class Texture;

class PlaneObject : public Behaviour
{
public:
	static PlaneObject* Create(const std::string& spriteName);

	PlaneObject(GameObject* gameObject, const std::string& name);

	void SetSpriteColor(const sm::Vec4& color);
	sm::Vec4 GetSpriteColor() const;
};
