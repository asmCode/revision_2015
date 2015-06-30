#include "PassageController.h"
#include "../GameObject.h"
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"
#include "../ScenesManager.h"
#include "../FuturisEngine/BehavioursManager.h"
#include <UserInput/Input.h>
#include <Utils/Random.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include <Math/Matrix.h>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

PassageController::PassageController(GameObject* gameObject, const std::string& name) :
	Behaviour(gameObject, name)
{
}

void PassageController::Awake()
{
	InitTiles();
}

void PassageController::Update()
{
	if (Input::GetKeyDown(KeyCode_R))
	{
		BlowTiles(200);

		for (uint32_t i = 0; i < 200; i++)
		{
			// m_tiles[Random::GetInt(0, m_tiles.size() - 1)]->Blow();
		}
	}
}

void PassageController::InitTiles()
{
	std::stringstream ss;

	int index = 0;
	GameObject* tileGameObject = NULL;

	do
	{
		ss.str("");
		ss.clear();
		ss << "scene.tile." << std::setw(2) << std::setfill('0') << index;
		tileGameObject = ScenesManager::GetInstance()->FindGameObject(ss.str());
		index++;

		if (tileGameObject != NULL)
		{
			Tile* tile = (Tile*)tileGameObject->AddComponent("Tile");

			m_tiles.push_back(tile);
		}

	} while (tileGameObject != NULL);
}

void PassageController::BlowTiles(int count)
{
	int index = 0;
	while (count > 0 && index < m_tiles.size())
	{
		if (!m_tiles[index]->IsDetached())
		{
			m_tiles[index]->Blow();
			count--;
		}

		index++;
	}
}

