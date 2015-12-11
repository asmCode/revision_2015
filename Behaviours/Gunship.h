#pragma once

#include "../Behaviour.h"
#include <Graphics/Point.h>
#include <Math/Quat.h>
#include <string>

class GameObject;
class Camera;

class Gunship : public Behaviour
{
public:
	Gunship(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

	void FireMachineGun(bool fire);
	void ToggleZoom();

	bool IsAbleToFire() const;

private:
	Camera* m_camera;

	bool m_isZoom;
};