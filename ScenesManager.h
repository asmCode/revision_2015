#pragma once

#include <vector>
#include <stdint.h>

class BaseScene;
class GameObject;

class ScenesManager
{
public:
	static ScenesManager* GetInstance();

	void Initialize();

	void Update(float time);
	BaseScene* GetActiveScene() const;
	bool IsSceneChanged() const;

	GameObject* FindGameObject(const std::string& name) const;

private:
	static ScenesManager* m_instance;

	std::vector<BaseScene*> m_scenes;
	int m_activeSceneIndex;

	bool m_isSceneChanged;

	ScenesManager();
	virtual ~ScenesManager() {}
};
