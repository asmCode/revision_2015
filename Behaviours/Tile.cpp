#include "Tile.h"
#include "../GameObject.h"
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"

Tile::Tile(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name),
	m_velocity(0, 0, 0)
{
}

void Tile::Update()
{
}

void Tile::Blow()
{
}

