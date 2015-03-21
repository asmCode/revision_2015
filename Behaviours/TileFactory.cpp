#include "TileFactory.h"
#include "Tile.h"

Behaviour* TileFactory::Create(GameObject* gameObject, const std::string& name)
{
	return new Tile(gameObject, name);
}
