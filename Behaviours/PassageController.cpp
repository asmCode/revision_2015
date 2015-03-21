#include "PassageController.h"
#include "../GameObject.h"
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include "../FuturisEngine/Time.h"
#include "../GraphicsLog.h"
#include "../ScenesManager.h"
#include "../FuturisEngine/BehavioursManager.h"

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
	} while (tileGameObject != NULL);
}

