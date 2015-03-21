#pragma once

#include "../Behaviour.h"
#include "../Behaviours/Tile.h"
#include <Math/Vec3.h>
#include <string>
#include <vector>

class GameObject;

class PassageController : public Behaviour
{
public:
	PassageController(GameObject* gameObject, const std::string& name);

	void Awake();
	void Update();

private:
	std::vector<Tile*> m_tiles;

	void InitTiles();
	void BlowTiles(int count);
};
